#pragma once

#include "CoreFramework.h"

#include "Window.h"
#include "Event.h"
#include "WindowEvent.h"

#include "Sprite.h"
#include "Texture.h"

namespace darnel {
    class OpenGL3Framework : public CoreFramework {
    public:
        Window* Init(int width, int height, std::string name) override;
        void Terminate() override;
        Window* CreateWindow(int width, int height, std::string name) override;
        bool WindowLoop(Window* window) override;

        std::shared_ptr<Sprite> MakeSprite(float x, float y, float width, float height, std::shared_ptr<Texture> texture) override;
        std::shared_ptr<Texture> MakeTexture(const std::string& path) override;
        std::shared_ptr<Texture> MakeTexture(unsigned char* buffer, int width, int height, int bpp) override;
        std::shared_ptr<Texture> MakeTexture(unsigned char r, unsigned char g, unsigned char b) override;
        std::shared_ptr<Texture> MakeTexture(unsigned char r, unsigned char g, unsigned char b, unsigned char a) override;

        void ImGuiInit(Window* window) override;
        void ImGuiNewFrame() override;
        void ImGuiRenderDrawData(ImDrawData* drawData) override;
        void ImGuiShutdown() override;

    private:
        void OnEvent(Event& e);
        bool OnWindowClose(WindowCloseEvent& e);

        bool m_Running = true;
    };
}
