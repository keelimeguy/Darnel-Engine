#pragma once

#include <vector>
#include <memory>

#include "Window.h"
#include "Sprite.h"
#include "Texture.h"

struct ImDrawData;

namespace darnel {
    class CoreFramework {
    public:
        virtual Window* Init(int width, int height, std::string name) = 0;
        virtual void Terminate() = 0;
        virtual Window* CreateWindow(int width, int height, std::string name) = 0;
        virtual bool WindowLoop(Window* window) = 0;

        virtual std::shared_ptr<Sprite> MakeSprite(float x, float y, float width, float height, std::shared_ptr<Texture> texture) = 0;
        virtual std::shared_ptr<Texture> MakeTexture(const std::string& path) = 0;
        virtual std::shared_ptr<Texture> MakeTexture(unsigned char* buffer, int width, int height, int bpp) = 0;
        virtual std::shared_ptr<Texture> MakeTexture(unsigned char r, unsigned char g, unsigned char b) = 0;
        virtual std::shared_ptr<Texture> MakeTexture(unsigned char r, unsigned char g, unsigned char b, unsigned char a) = 0;

        virtual void ImGuiInit(Window* window) = 0;
        virtual void ImGuiNewFrame() = 0;
        virtual void ImGuiRenderDrawData(ImDrawData* drawData) = 0;
        virtual void ImGuiShutdown() = 0;
    protected:
        std::vector<std::unique_ptr<Window>> m_windows;
    };
}
