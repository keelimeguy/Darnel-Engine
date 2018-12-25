#include "DirectX12Renderer.h"

// Data
static int const                         NUM_FRAMES_IN_FLIGHT = 3;
static FrameContext                      g_frameContext[NUM_FRAMES_IN_FLIGHT] = {};
static UINT                              g_frameIndex = 0;

static int const                         NUM_BACK_BUFFERS = 3;
static ComPtr<ID3D12Device2>             g_pd3dDevice;
static ComPtr<ID3D12DescriptorHeap>      g_pd3dRtvDescHeap;
static ComPtr<ID3D12DescriptorHeap>      g_pd3dSrvDescHeap;
static ComPtr<ID3D12CommandQueue>        g_pd3dCommandQueue;
static ComPtr<ID3D12GraphicsCommandList> g_pd3dCommandList;
static ComPtr<ID3D12Fence>               g_fence;
static HANDLE                            g_fenceEvent = NULL;
static UINT64                            g_fenceLastSignaledValue = 0;
static ComPtr<IDXGISwapChain4>           g_pSwapChain;
static HANDLE                            g_hSwapChainWaitableObject = NULL;
static ComPtr<ID3D12Resource>            g_mainRenderTargetResource[NUM_BACK_BUFFERS] = {};
static D3D12_CPU_DESCRIPTOR_HANDLE       g_mainRenderTargetDescriptor[NUM_BACK_BUFFERS] = {};

static MSG gs_msg;
static bool gs_allowTearing = false;
static bool gs_Fullscreen = false;
static FrameContext* gs_curFrameCtxt;
static bool gs_useWarp = false;

void CreateRenderTarget() {
    ComPtr<ID3D12Resource> pBackBuffer;
    for (UINT i = 0; i < NUM_BACK_BUFFERS; ++i) {
        g_pSwapChain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer));
        g_pd3dDevice->CreateRenderTargetView(pBackBuffer.Get(), NULL, g_mainRenderTargetDescriptor[i]);
        g_mainRenderTargetResource[i] = pBackBuffer;
    }
}

void WaitForLastSubmittedFrame() {
    FrameContext* frameCtxt = &g_frameContext[g_frameIndex % NUM_FRAMES_IN_FLIGHT];

    UINT64 fenceValue = frameCtxt->FenceValue;
    if (fenceValue == 0)
        return; // No fence was signaled

    frameCtxt->FenceValue = 0;
    if (g_fence->GetCompletedValue() >= fenceValue)
        return;

    g_fence->SetEventOnCompletion(fenceValue, g_fenceEvent);
    WaitForSingleObject(g_fenceEvent, INFINITE);
}

FrameContext* WaitForNextFrameResources() {
    UINT nextFrameIndex = g_frameIndex + 1;
    g_frameIndex = nextFrameIndex;

    HANDLE waitableObjects[] = { g_hSwapChainWaitableObject, NULL };
    DWORD numWaitableObjects = 1;

    FrameContext* frameCtxt = &g_frameContext[nextFrameIndex % NUM_FRAMES_IN_FLIGHT];
    UINT64 fenceValue = frameCtxt->FenceValue;
    if (fenceValue != 0) { // means no fence was signaled
        frameCtxt->FenceValue = 0;
        g_fence->SetEventOnCompletion(fenceValue, g_fenceEvent);
        waitableObjects[1] = g_fenceEvent;
        numWaitableObjects = 2;
    }

    WaitForMultipleObjects(numWaitableObjects, waitableObjects, TRUE, INFINITE);

    return frameCtxt;
}

void ResizeSwapChain(HWND hWnd, int width, int height) {

    int ClientWidth = std::max(1, width);
    int ClientHeight = std::max(1, height);

    ComPtr<IDXGIFactory4> dxgiFactory;
    g_pSwapChain->GetParent(IID_PPV_ARGS(&dxgiFactory));

    CloseHandle(g_hSwapChainWaitableObject);

    DXGI_SWAP_CHAIN_DESC sd = {};
    ThrowIfFailed(g_pSwapChain->GetDesc(&sd));
    ThrowIfFailed(g_pSwapChain->ResizeBuffers(NUM_BACK_BUFFERS, ClientWidth, ClientHeight, sd.BufferDesc.Format, sd.Flags));

    g_pSwapChain->SetMaximumFrameLatency(NUM_BACK_BUFFERS);
    g_hSwapChainWaitableObject = g_pSwapChain->GetFrameLatencyWaitableObject();
    assert(g_hSwapChainWaitableObject != NULL);
}

void CleanupRenderTarget() {
    WaitForLastSubmittedFrame();

    for (UINT i = 0; i < NUM_BACK_BUFFERS; ++i)
        g_mainRenderTargetResource[i].Reset();
}

bool CheckTearingSupport() {
    bool allowTearing = false;

    // Rather than create the DXGI 1.5 factory interface directly, we create the
    // DXGI 1.4 interface and query for the 1.5 interface. This is to enable the
    // graphics debugging tools which will not support the 1.5 factory interface
    // until a future update.
    ComPtr<IDXGIFactory4> factory4;
    if (SUCCEEDED(CreateDXGIFactory1(IID_PPV_ARGS(&factory4)))) {
        ComPtr<IDXGIFactory5> factory5;
        if (SUCCEEDED(factory4.As(&factory5))) {
            if (FAILED(factory5->CheckFeatureSupport(
                DXGI_FEATURE_PRESENT_ALLOW_TEARING,
                &allowTearing, sizeof(allowTearing))))
            {
                allowTearing = false;
            }
        }
    }

    return allowTearing;
}

ComPtr<IDXGIAdapter4> GetAdapter(bool useWarp) {
    ComPtr<IDXGIFactory4> dxgiFactory;
    UINT createFactoryFlags = 0;
#if defined(DX12_ENABLE_DEBUG_LAYER)
    createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif

    ThrowIfFailed(CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&dxgiFactory)));

    ComPtr<IDXGIAdapter1> dxgiAdapter1;
    ComPtr<IDXGIAdapter4> dxgiAdapter4;

    if (useWarp) {
        ThrowIfFailed(dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&dxgiAdapter1)));
        // It is neither safe nor reliable to perform a static_cast on COM objects.
        ThrowIfFailed(dxgiAdapter1.As(&dxgiAdapter4));

    } else {
        SIZE_T maxDedicatedVideoMemory = 0;
        for (UINT i = 0; dxgiFactory->EnumAdapters1(i, &dxgiAdapter1) != DXGI_ERROR_NOT_FOUND; ++i) {
            DXGI_ADAPTER_DESC1 dxgiAdapterDesc1;
            dxgiAdapter1->GetDesc1(&dxgiAdapterDesc1);

            // Check to see if the adapter can create a D3D12 device without actually
            // creating it. The adapter with the largest dedicated video memory
            // is favored.
            if ((dxgiAdapterDesc1.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) == 0 &&
                SUCCEEDED(D3D12CreateDevice(dxgiAdapter1.Get(),
                    D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), nullptr)) &&
                dxgiAdapterDesc1.DedicatedVideoMemory > maxDedicatedVideoMemory )
            {
                maxDedicatedVideoMemory = dxgiAdapterDesc1.DedicatedVideoMemory;
                // It is neither safe nor reliable to perform a static_cast on COM objects.
                ThrowIfFailed(dxgiAdapter1.As(&dxgiAdapter4));
            }
        }
    }

    return dxgiAdapter4;
}

HRESULT CreateDeviceD3D(HWND hWnd) {
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC1 sd;
    {
        ZeroMemory(&sd, sizeof(sd));
        sd.Width = 0;
        sd.Height = 0;
        sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.Stereo = FALSE;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.BufferCount = NUM_BACK_BUFFERS;
        sd.Scaling = DXGI_SCALING_STRETCH;
        sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        sd.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
        gs_allowTearing = CheckTearingSupport();
        sd.Flags = ( gs_allowTearing ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0) | DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
    }

#if defined(DX12_ENABLE_DEBUG_LAYER)
    ComPtr<ID3D12Debug> dx12Debug;
    ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&dx12Debug)));
    dx12Debug->EnableDebugLayer();
#endif

    ComPtr<IDXGIAdapter4> adapter = GetAdapter(gs_useWarp);
    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
    ThrowIfFailed(D3D12CreateDevice(adapter.Get(), featureLevel, IID_PPV_ARGS(&g_pd3dDevice)));

#if defined(DX12_ENABLE_DEBUG_LAYER)
    ComPtr<ID3D12InfoQueue> pInfoQueue;
    if (SUCCEEDED(g_pd3dDevice.As(&pInfoQueue))) {
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, TRUE);
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, TRUE);
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, TRUE);

        // Suppress whole categories of messages
        //D3D12_MESSAGE_CATEGORY Categories[] = {};

        // Suppress messages based on their severity level
        D3D12_MESSAGE_SEVERITY Severities[] =
        {
            D3D12_MESSAGE_SEVERITY_INFO
        };

        // Suppress individual messages by their ID
        // D3D12_MESSAGE_ID DenyIds[] = {};

        D3D12_INFO_QUEUE_FILTER NewFilter = {};
        //NewFilter.DenyList.NumCategories = _countof(Categories);
        //NewFilter.DenyList.pCategoryList = Categories;
        NewFilter.DenyList.NumSeverities = _countof(Severities);
        NewFilter.DenyList.pSeverityList = Severities;
        // NewFilter.DenyList.NumIDs = _countof(DenyIds);
        // NewFilter.DenyList.pIDList = DenyIds;

        ThrowIfFailed(pInfoQueue->PushStorageFilter(&NewFilter));
    }
#endif

    {
        D3D12_DESCRIPTOR_HEAP_DESC desc = {};
        desc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        desc.NumDescriptors = NUM_BACK_BUFFERS;
        desc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        desc.NodeMask       = 1;
        ThrowIfFailed(g_pd3dDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&g_pd3dRtvDescHeap)));

        SIZE_T rtvDescriptorSize = g_pd3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = g_pd3dRtvDescHeap->GetCPUDescriptorHandleForHeapStart();
        for (UINT i = 0; i < NUM_BACK_BUFFERS; ++i) {
            g_mainRenderTargetDescriptor[i] = rtvHandle;
            rtvHandle.ptr += rtvDescriptorSize;
        }
    }

    {
        D3D12_DESCRIPTOR_HEAP_DESC desc = {};
        desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        desc.NumDescriptors = 1;
        desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
        ThrowIfFailed(g_pd3dDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&g_pd3dSrvDescHeap)));
    }

    {
        D3D12_COMMAND_QUEUE_DESC desc = {};
        desc.Type     = D3D12_COMMAND_LIST_TYPE_DIRECT;
        desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
        desc.Flags    = D3D12_COMMAND_QUEUE_FLAG_NONE;
        desc.NodeMask = 1;
        ThrowIfFailed(g_pd3dDevice->CreateCommandQueue(&desc, IID_PPV_ARGS(&g_pd3dCommandQueue)));
    }

    for (UINT i = 0; i < NUM_FRAMES_IN_FLIGHT; ++i)
        ThrowIfFailed(g_pd3dDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&g_frameContext[i].CommandAllocator)));

    ThrowIfFailed(g_pd3dDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, g_frameContext[0].CommandAllocator.Get(), NULL, IID_PPV_ARGS(&g_pd3dCommandList)));
    ThrowIfFailed(g_pd3dCommandList->Close());

    ThrowIfFailed(g_pd3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&g_fence)));

    g_fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    assert(g_fenceEvent && "Failed to create fence event.");

    {
        ComPtr<IDXGISwapChain1> swapChain1;
        ComPtr<IDXGIFactory4> dxgiFactory;
        UINT createFactoryFlags = 0;
#if defined(DX12_ENABLE_DEBUG_LAYER)
        createFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;
#endif
        ThrowIfFailed(CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&dxgiFactory)));
        ThrowIfFailed(dxgiFactory->CreateSwapChainForHwnd(g_pd3dCommandQueue.Get(), hWnd, &sd, NULL, NULL, &swapChain1));
        // Disable the Alt+Enter fullscreen toggle feature. Switching to fullscreen
        // will be handled manually.
        ThrowIfFailed(dxgiFactory->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER));
        ThrowIfFailed(swapChain1.As(&g_pSwapChain));
        g_pSwapChain->SetMaximumFrameLatency(NUM_BACK_BUFFERS);
        g_hSwapChainWaitableObject = g_pSwapChain->GetFrameLatencyWaitableObject();
    }

    CreateRenderTarget();

    ZeroMemory(&gs_msg, sizeof(gs_msg));

    return S_OK;
}

bool WindowLoop() {
    // Poll and handle messages (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    while (PeekMessage(&gs_msg, NULL, 0U, 0U, PM_REMOVE)) {
        TranslateMessage(&gs_msg);
        DispatchMessage(&gs_msg);
    }

    return gs_msg.message != WM_QUIT;
}

void DX12_initImGui() {
    ImGui_ImplDX12_Init(g_pd3dDevice.Get(), NUM_FRAMES_IN_FLIGHT,
        DXGI_FORMAT_R8G8B8A8_UNORM,
        g_pd3dSrvDescHeap->GetCPUDescriptorHandleForHeapStart(),
        g_pd3dSrvDescHeap->GetGPUDescriptorHandleForHeapStart()
    );
}

void DX12_RenderDrawData(ImDrawData* drawData) {
    ImGui_ImplDX12_RenderDrawData(drawData, g_pd3dCommandList.Get());
}

void CleanupDeviceD3D() {
    CleanupRenderTarget();
    if (g_hSwapChainWaitableObject) { CloseHandle(g_hSwapChainWaitableObject); }
    if (g_fenceEvent) { CloseHandle(g_fenceEvent); }
}

void BeginRender() {
    gs_curFrameCtxt = WaitForNextFrameResources();
    UINT backBufferIdx = g_pSwapChain->GetCurrentBackBufferIndex();
    gs_curFrameCtxt->CommandAllocator->Reset();
    g_pd3dCommandList->Reset(gs_curFrameCtxt->CommandAllocator.Get(), nullptr);

    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource   = g_mainRenderTargetResource[backBufferIdx].Get();
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_RENDER_TARGET;

    g_pd3dCommandList->ResourceBarrier(1, &barrier);

    // Clear the render target.
    float clearColor[] = { 0.4f, 0.6f, 0.9f, 1.0f };
    g_pd3dCommandList->ClearRenderTargetView(g_mainRenderTargetDescriptor[backBufferIdx], clearColor, 0, nullptr);

    g_pd3dCommandList->OMSetRenderTargets(1, &g_mainRenderTargetDescriptor[backBufferIdx], false, NULL);
    ID3D12DescriptorHeap* const ppHeaps[] = { g_pd3dSrvDescHeap.Get() };
    g_pd3dCommandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
}

void EndRender() {
    UINT backBufferIdx = g_pSwapChain->GetCurrentBackBufferIndex();

    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource   = g_mainRenderTargetResource[backBufferIdx].Get();
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_PRESENT;

    g_pd3dCommandList->ResourceBarrier(1, &barrier);
    g_pd3dCommandList->Close();

    ID3D12CommandList* const commandLists[] = { g_pd3dCommandList.Get() };
    g_pd3dCommandQueue->ExecuteCommandLists(_countof(commandLists), commandLists);

    UINT syncInterval = 1; // g_VSync ? 1 : 0;
    UINT presentFlags = gs_allowTearing && !syncInterval ? DXGI_PRESENT_ALLOW_TEARING : 0;
    g_pSwapChain->Present(syncInterval, presentFlags);

    UINT64 fenceValue = g_fenceLastSignaledValue + 1;
    g_pd3dCommandQueue->Signal(g_fence.Get(), fenceValue);
    g_fenceLastSignaledValue = fenceValue;
    gs_curFrameCtxt->FenceValue = fenceValue;
}

/*void SetFullscreen(bool fullscreen) {
    if (gs_Fullscreen != fullscreen) {
        gs_Fullscreen = fullscreen;

        if (gs_Fullscreen) // Switching to fullscreen.
        {
            // Store the current window dimensions so they can be restored
            // when switching out of fullscreen state.
            GetWindowRect(gs_hwnd, &gs_WindowRect);

            // Set the window style to a borderless window so the client area fills
            // the entire screen.
            UINT windowStyle = WS_OVERLAPPEDWINDOW & ~(WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);

            SetWindowLongW(gs_hwnd, GWL_STYLE, windowStyle);

            // Query the name of the nearest display device for the window.
            // This is required to set the fullscreen dimensions of the window
            // when using a multi-monitor setup.
            HMONITOR hMonitor = MonitorFromWindow(gs_hwnd, MONITOR_DEFAULTTONEAREST);
            MONITORINFOEX monitorInfo = {};
            monitorInfo.cbSize = sizeof(MONITORINFOEX);
            GetMonitorInfo(hMonitor, &monitorInfo);

            SetWindowPos(gs_hwnd, HWND_TOP,
                monitorInfo.rcMonitor.left,
                monitorInfo.rcMonitor.top,
                monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left,
                monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top,
                SWP_FRAMECHANGED | SWP_NOACTIVATE);

            ShowWindow(gs_hwnd, SW_MAXIMIZE);
        } else {
            // Restore all the window decorators.
            SetWindowLong(gs_hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);

            SetWindowPos(gs_hwnd, HWND_NOTOPMOST,
                gs_WindowRect.left,
                gs_WindowRect.top,
                gs_WindowRect.right - gs_WindowRect.left,
                gs_WindowRect.bottom - gs_WindowRect.top,
                SWP_FRAMECHANGED | SWP_NOACTIVATE);

            ShowWindow(gs_hwnd, SW_NORMAL);
        }
    }
}*/

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg) {
        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
            {
                bool alt = (::GetAsyncKeyState(VK_MENU) & 0x8000) != 0;
                switch (wParam) {
                    case VK_ESCAPE:
                        PostQuitMessage(0);
                        break;
                    case VK_RETURN:
                        if ( alt )
                    case VK_F11:
                        {
                            //SetFullscreen(!gs_Fullscreen);
                        }
                        break;
                }
            }
            break;
        case WM_SYSCHAR: // Stop playing system notification sound
            break;
        case WM_SIZE:
            if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED) {
                ImGui_ImplDX12_InvalidateDeviceObjects();
                CleanupRenderTarget();
                ResizeSwapChain(hWnd, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam));
                CreateRenderTarget();
                ImGui_ImplDX12_CreateDeviceObjects();
            }
            return 0;
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
                return 0;
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hWnd, msg, wParam, lParam);
}
