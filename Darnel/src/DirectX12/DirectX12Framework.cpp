#include "DirectX12Framework.h"
#include "DirectX12Window.h"
// #include "DirectX12Sprite.h"
// #include "DirectX12Texture.h"

#include "DirectX12Renderer.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx12.h"

#include <string>
#include <iostream>
#include <algorithm>
#include <cassert>

namespace darnel {
    Window* DirectX12Framework::Init(int width, int height, std::string name) {
        SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

        // Create application window
        Window* window = CreateWindow(width, height, name);
        if (!window) return nullptr;

        // Initialize Direct3D
        if (CreateDeviceD3D(((DirectX12Window*)window)->m_hwnd) < 0) {
            CleanupDeviceD3D();
            return nullptr;
        }

        // Show the window
        window->MakeActive();

        return window;
    }

    void DirectX12Framework::Terminate() {
        CleanupDeviceD3D();
        UnregisterClassW(DirectX12Window::s_windowClassName, DirectX12Window::s_wc.hInstance);
    }

    Window* DirectX12Framework::CreateWindow(int width, int height, std::string name) {
        m_windows.push_back(std::make_unique<DirectX12Window>(width, height, name));
        if (!m_windows.back()->IsValid()) {
            m_windows.pop_back();
            return nullptr;
        }
        return m_windows.back().get();
    }

    std::shared_ptr<Sprite> DirectX12Framework::MakeSprite(float x, float y, float width, float height, std::shared_ptr<Texture> texture) {
        return nullptr;
        // return std::make_shared<DirectX12Sprite>(x, y, width, height, texture);
    }

    std::shared_ptr<Texture> DirectX12Framework::MakeTexture(const std::string& path) {
        return nullptr;
        // return std::make_shared<DirectX12Texture>(path);
    }

    std::shared_ptr<Texture> DirectX12Framework::MakeTexture(unsigned char* buffer, int width, int height, int bpp) {
        return nullptr;
        // return std::make_shared<DirectX12Texture>(buffer, width, height, bpp);
    }

    std::shared_ptr<Texture> DirectX12Framework::MakeTexture(unsigned char r, unsigned char g, unsigned char b) {
        return nullptr;
        // return std::make_shared<DirectX12Texture>(r, g, b);
    }

    std::shared_ptr<Texture> DirectX12Framework::MakeTexture(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        return nullptr;
        // return std::make_shared<DirectX12Texture>(r, g, b, a);
    }

    bool DirectX12Framework::WindowLoop(Window* window) {
        return ::WindowLoop();
    }

    void DirectX12Framework::ImGuiInit(Window* window) {
        ImGui_ImplWin32_Init(((DirectX12Window*)window)->m_hwnd);
        // ImGui_ImplDX12_Init(g_pd3dDevice.Get(), NUM_FRAMES_IN_FLIGHT,
        //     DXGI_FORMAT_R8G8B8A8_UNORM,
        //     g_pd3dSrvDescHeap->GetCPUDescriptorHandleForHeapStart(),
        //     g_pd3dSrvDescHeap->GetGPUDescriptorHandleForHeapStart()
        // );
        ::DX12_initImGui();
    }

    void DirectX12Framework::ImGuiNewFrame() {
        ImGui_ImplDX12_NewFrame();
        ImGui_ImplWin32_NewFrame();
    }

    void DirectX12Framework::ImGuiRenderDrawData(ImDrawData* drawData) {
        ::DX12_RenderDrawData(drawData);
        // ImGui_ImplDX12_RenderDrawData(drawData, g_pd3dCommandList.Get());
    }

    void DirectX12Framework::ImGuiShutdown() {
        ImGui_ImplDX12_Shutdown();
        ImGui_ImplWin32_Shutdown();
    }
}
