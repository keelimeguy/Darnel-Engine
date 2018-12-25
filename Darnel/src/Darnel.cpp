#include "CoreFramework.h"
#include "OpenGL3Framework.h"

#include "Sprite.h"
#include "OpenGL3Sprite.h"

#include "Texture.h"
#include "OpenGL3Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>

#include <iostream>
#include <memory>

static std::unique_ptr<darnel::CoreFramework> gs_Framework = std::make_unique<darnel::OpenGL3Framework>();
static darnel::Window* gs_curWindow;

namespace darnel {
    bool Init(int width, int height, std::string name) {
        Window* window = gs_Framework->Init(width, height, name);
        if (window == NULL) {
            gs_Framework->Terminate();
            return false;
        }

        if (!window->IsValid()) return false;
        gs_curWindow = window;
        return true;
    }

    bool CreateWindow(int width, int height, std::string name) {
        Window* window = gs_Framework->CreateWindow(width, height, name);
        if (!window->IsValid()) return false;

        gs_curWindow = window;
        gs_curWindow->MakeActive();
        return true;
    }

    void Terminate() {
        return gs_Framework->Terminate();
    }

    bool WindowLoop() {
        return gs_Framework->WindowLoop(gs_curWindow);
    }

    void ClearWindow(float f1, float f2, float f3, float f4) {
        gs_curWindow->Clear(f1, f2, f3, f4);
    }

    std::shared_ptr<Sprite> MakeSprite(float x, float y, float width, float height, std::shared_ptr<Texture> texture) {
        return std::make_shared<OpenGL3Sprite>(x, y, width, height, texture);
    }

    std::shared_ptr<Texture> MakeTexture(const std::string& path) {
        return std::make_shared<OpenGL3Texture>(path);
    }

    std::shared_ptr<Texture> MakeTexture(unsigned char* buffer, int width, int height, int bpp) {
        return std::make_shared<OpenGL3Texture>(buffer, width, height, bpp);
    }

    std::shared_ptr<Texture> MakeTexture(unsigned char r, unsigned char g, unsigned char b) {
        return std::make_shared<OpenGL3Texture>(r, g, b);
    }

    std::shared_ptr<Texture> MakeTexture(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        return std::make_shared<OpenGL3Texture>(r, g, b, a);
    }

    void ImGui_Init() {
        gs_Framework->ImGuiInit(gs_curWindow);
    }

    void ImGui_NewFrame() {
        gs_Framework->ImGuiNewFrame();
    }

    void ImGui_RenderDrawData(ImDrawData* drawData) {
        gs_Framework->ImGuiRenderDrawData(drawData);
    }

    void ImGui_Shutdown() {
        gs_Framework->ImGuiShutdown();
    }
}
