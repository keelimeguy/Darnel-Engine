#pragma once

#include "Renderer.h"
#include <string>

class Texture {
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;

    void Init();

public:
    Texture(const std::string& path);
    Texture(unsigned char* buffer, int width, int height, int bpp);
    Texture(unsigned char r, unsigned char g, unsigned char b);
    Texture(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
};

