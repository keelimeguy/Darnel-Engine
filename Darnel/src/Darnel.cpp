#include "CoreFramework.h"
#include "OpenGL3Framework.h"

#include "Darnel.h"
#include "Sprite.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>

#include <iostream>
#include <memory>

static std::unique_ptr<darnel::CoreFramework> gs_Framework = std::make_unique<darnel::OpenGL3Framework>();

namespace darnel {
    bool Init(int width, int height, std::string name) {
        Window* window = gs_Framework->Init(width, height, name);
        if (window == nullptr) {
            gs_Framework->Terminate();
            return false;
        }

        if (!window->IsValid()) return false;
        return true;
    }

    bool CreateWindow(int width, int height, std::string name) {
        Window* window = gs_Framework->CreateWindow(width, height, name);
        if (window == nullptr || !window->IsValid()) return false;
        return true;
    }

    bool CloseWindow(std::string name) {
        Window* window = gs_Framework->GetWindow(name);
        if (window == nullptr || !window->IsValid()) return false;
        window->Close();
        return true;
    }

    bool SetWindowContext(std::string name, bool flush) {
        Window* window = gs_Framework->GetWindow(name);
        if (window == nullptr || !window->IsValid()) return false;

        if (flush) Flush();
        window->MakeActiveContext();
        return true;
    }

    std::string GetActiveWindow() {
        return gs_Framework->GetActiveWindow()->GetName();
    }

    void Terminate() {
        gs_Framework->Terminate();
    }

    void Flush() {
        gs_Framework->GetActiveWindow()->OnRender();
    }

    bool WindowLoop() {
        gs_Framework->PollEvents();
        if (!gs_Framework->IsRunning()) return false;
        return true;
    }

    void ClearWindow(float f1, float f2, float f3, float f4) {
        gs_Framework->GetActiveWindow()->Clear(f1, f2, f3, f4);
    }

    std::shared_ptr<Sprite> MakeSprite(float x, float y, float width, float height, std::shared_ptr<Texture> texture) {
        return gs_Framework->MakeSprite(x, y, width, height, texture);
    }

    std::shared_ptr<Texture> MakeTexture(const std::string& path) {
        return gs_Framework->MakeTexture(path);
    }

    std::shared_ptr<Texture> MakeTexture(unsigned char* buffer, int width, int height, int bpp) {
        return gs_Framework->MakeTexture(buffer, width, height, bpp);
    }

    std::shared_ptr<Texture> MakeTexture(unsigned char r, unsigned char g, unsigned char b) {
        return gs_Framework->MakeTexture(r, g, b);
    }

    std::shared_ptr<Texture> MakeTexture(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        return gs_Framework->MakeTexture(r, g, b, a);
    }

    void ImGui_Init() {
        gs_Framework->ImGuiInit();
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
