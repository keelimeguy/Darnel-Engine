#pragma once

#include "Window.h"
#include "DirectX12Framework.h"

#include "DirectX12Renderer.h"

#include <memory>

namespace darnel {
    class DirectX12Window : public Window {
    public:
        DirectX12Window(int width, int height, std::string name);
        ~DirectX12Window();

        void MakeActive() override;
        void Clear(float f0, float f1, float f2, float f3) override;
    private:
        static WNDCLASSEXW s_wc;
        static bool s_registered;
        static const wchar_t* s_windowClassName;

        HWND m_hwnd;
        RECT m_windowRect;

        friend class DirectX12Framework;
    };
}
