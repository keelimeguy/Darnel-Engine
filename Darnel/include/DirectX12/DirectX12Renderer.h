#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#if defined(CreateWindow)
#undef CreateWindow
#endif

#include <wrl.h>
using namespace Microsoft::WRL;

#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#if defined(min)
#undef min
#endif

#if defined(max)
#undef max
#endif

#define DX12_ENABLE_DEBUG_LAYER

// namespace darnel {
//     class DirectX12Renderer {
//     public:
//     };
// }

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx12.h"

#include <algorithm>

struct FrameContext
{
    ComPtr<ID3D12CommandAllocator> CommandAllocator;
    UINT64                  FenceValue;
};

inline void ThrowIfFailed(HRESULT hr) {
	if (FAILED(hr)) {
		throw std::exception();
	}
}

void CreateRenderTarget();
void WaitForLastSubmittedFrame();
FrameContext* WaitForNextFrameResources();
void ResizeSwapChain(HWND hWnd, int width, int height);
void CleanupRenderTarget();
bool CheckTearingSupport();
ComPtr<IDXGIAdapter4> GetAdapter(bool useWarp);
HRESULT CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
bool WindowLoop();
void BeginRender();
void EndRender();
//void SetFullscreen(bool fullscreen);

void DX12_initImGui();
void DX12_RenderDrawData(ImDrawData* drawData);

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
