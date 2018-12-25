#include "Texture.h"

#include "OpenGL3Texture.h"

namespace darnel {
    Texture::Texture(const std::string& path) {
        m_texture = std::make_shared<OpenGL3Texture>(path);
    }

    Texture::Texture(unsigned char* buffer, int width, int height, int bpp) {
        m_texture = std::make_shared<OpenGL3Texture>(buffer, width, height, bpp);
    }

    Texture::Texture(unsigned char r, unsigned char g, unsigned char b) {
        m_texture = std::make_shared<OpenGL3Texture>(r, g, b);
    }

    Texture::Texture(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        m_texture = std::make_shared<OpenGL3Texture>(r, g, b, a);
    }

    void Texture::Bind(unsigned int slot) const {
        m_texture->Bind(slot);
    }

    void Texture::Unbind() const {
        m_texture->Unbind();
    }

	inline int Texture::GetWidth() const {
		return m_texture->GetWidth();
	}

	inline int Texture::GetHeight() const {
		return m_texture->GetHeight();
	}
}
