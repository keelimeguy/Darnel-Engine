#pragma once

#include <string>

namespace darnel {
    class Texture {
    public:
        Texture(const std::string& path) {}
        Texture(unsigned char* buffer, int width, int height, int bpp)
            : m_LocalBuffer(buffer), m_Width(width), m_Height(height), m_BPP(bpp) {}
        Texture(unsigned char r, unsigned char g, unsigned char b) {}
        Texture(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {}
        virtual ~Texture() {}

        inline int GetWidth() const { return m_Width; }
        inline int GetHeight() const { return m_Height; }

        virtual void Bind(unsigned int slot = 0) const = 0;
        virtual void Unbind() const = 0;

    protected:
        unsigned char* m_LocalBuffer;
        int m_Width, m_Height, m_BPP;
    };
}
