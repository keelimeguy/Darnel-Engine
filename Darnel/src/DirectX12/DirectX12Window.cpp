#include "DirectX12Window.h"

#include "DirectX12Renderer.h"

static std::wstring s2ws(const std::string& s) {
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

namespace darnel {
    const wchar_t* DirectX12Window::s_windowClassName = L"DirectX12Window";
    WNDCLASSEXW DirectX12Window::s_wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, s_windowClassName, NULL };
    bool DirectX12Window::s_registered = false;

    DirectX12Window::DirectX12Window(int width, int height, std::string name)
    {
        if (!s_registered) {
            s_registered = true;
            RegisterClassExW(&s_wc);
        }

        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);

        RECT windowRect = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
        AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

        int windowWidth = windowRect.right - windowRect.left;
        int windowHeight = windowRect.bottom - windowRect.top;

        // Center the window within the screen. Clamp to 0, 0 for the top-left corner.
        int windowX = std::max<int>(0, (screenWidth - windowWidth) / 2);
        int windowY = std::max<int>(0, (screenHeight - windowHeight) / 2);

        std::wstring stemp = s2ws(name);

        m_hwnd = CreateWindowExW(
            NULL,
            s_windowClassName,
            stemp.c_str(),
            WS_OVERLAPPEDWINDOW,
            windowX,
            windowY,
            windowWidth,
            windowHeight,
            NULL,
            NULL,
            s_wc.hInstance,
            nullptr
        );

        m_valid = (m_hwnd != NULL);
        if (m_valid)
            GetWindowRect(m_hwnd, &m_windowRect);
    }

    DirectX12Window::~DirectX12Window() {
        DestroyWindow(m_hwnd);
    }

    void DirectX12Window::MakeActive() {
        ShowWindow(m_hwnd, SW_SHOWDEFAULT);
        UpdateWindow(m_hwnd);
    }

    void DirectX12Window::Clear(float f0, float f1, float f2, float f3) {
        //TODO
    }
}
