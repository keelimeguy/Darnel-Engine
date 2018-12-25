#pragma once

#include "Texture.h"

#include <string>

namespace darnel {
    class OpenGL3Texture : public Texture {
    private:
        unsigned int m_RendererID;
        std::string m_FilePath;

        void Init();
    public:
        OpenGL3Texture(const std::string& path);
        OpenGL3Texture(unsigned char* buffer, int width, int height, int bpp);
        OpenGL3Texture(unsigned char r, unsigned char g, unsigned char b);
        OpenGL3Texture(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
        ~OpenGL3Texture();

        void Bind(unsigned int slot = 0) const override;
        void Unbind() const override;
    };
}
