#pragma once

#include <memory>
#include <string>

class Texture;

namespace darnel {
    class Texture {
    public:
        Texture(const std::string& path);
        Texture(unsigned char* buffer, int width, int height, int bpp);
        Texture(unsigned char r, unsigned char g, unsigned char b);
        Texture(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

        void Bind(unsigned int slot = 0) const;
        void Unbind() const;

		inline int GetWidth() const;
		inline int GetHeight() const;
    private:
        std::shared_ptr<::Texture> m_texture;
    };
}
