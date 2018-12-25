#pragma once

#include <string>
#include <memory>

#include "Sprite.h"
#include "Texture.h"

struct ImDrawData;

namespace darnel {
    bool Init(int width, int height, std::string name);
    bool CreateWindow(int width, int height, std::string name);
    void Terminate();
    bool WindowLoop();
    void ClearWindow(float f1, float f2, float f3, float f4);

    std::shared_ptr<Sprite> MakeSprite(float x, float y, float width, float height, std::shared_ptr<Texture> texture);
    std::shared_ptr<Texture> MakeTexture(const std::string& path);
    std::shared_ptr<Texture> MakeTexture(unsigned char* buffer, int width, int height, int bpp);
    std::shared_ptr<Texture> MakeTexture(unsigned char r, unsigned char g, unsigned char b);
    std::shared_ptr<Texture> MakeTexture(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

    void ImGui_Init();
    void ImGui_NewFrame();
    void ImGui_RenderDrawData(ImDrawData* drawData);
    void ImGui_Shutdown();
}
