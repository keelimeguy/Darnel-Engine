#include "OpenGL3Texture.h"
#include "OpenGL3Renderer.h"

#include <stb_image.h>

namespace darnel {
    std::shared_ptr<Texture> Texture::Create(const std::string &path) {
        return std::shared_ptr<Texture>(new OpenGL3Texture(path));
    }

    std::shared_ptr<Texture> Texture::Create(unsigned char *buffer, int width, int height, int bpp) {
        return std::shared_ptr<Texture>(new OpenGL3Texture(buffer, width, height, bpp));
    }

    std::shared_ptr<Texture> Texture::Create(unsigned char r, unsigned char g, unsigned char b) {
        return std::shared_ptr<Texture>(new OpenGL3Texture(r, g, b));
    }

    std::shared_ptr<Texture> Texture::Create(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        return std::shared_ptr<Texture>(new OpenGL3Texture(r, g, b, a));
    }

    void OpenGL3Texture::Init() {
        GLCALL(glGenTextures(1, &m_RendererID));
        GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));

        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

        GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
        GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
    }

    OpenGL3Texture::OpenGL3Texture(const std::string &path)
        : Texture(nullptr, 0, 0, 0), m_RendererID(0), m_FilePath(path) {
        stbi_set_flip_vertically_on_load(1);
        m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

        Init();

        if (m_LocalBuffer)
            stbi_image_free(m_LocalBuffer);
    }

    OpenGL3Texture::OpenGL3Texture(unsigned char *buffer, int width, int height, int bpp)
        : Texture(nullptr, width, height, bpp), m_RendererID(0), m_FilePath("") {
        m_LocalBuffer = new unsigned char[4 * width * height];
        for (int i = 0, j = 0; i < 4 * width * height; ++i) {
            if (bpp < 4 && i % 4 >= bpp)
                m_LocalBuffer[i] = (unsigned char)255;
            else
                m_LocalBuffer[i] = buffer[j++];
        }

        Init();
    }

    OpenGL3Texture::OpenGL3Texture(unsigned char r, unsigned char g, unsigned char b)
        : Texture(nullptr, 1, 1, 3), m_RendererID(0), m_FilePath("") {
        m_LocalBuffer = new unsigned char[4];
        m_LocalBuffer[0] = r; m_LocalBuffer[1] = g; m_LocalBuffer[2] = b; m_LocalBuffer[3] = (unsigned char)255;

        Init();
    }

    OpenGL3Texture::OpenGL3Texture(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
        : Texture(nullptr, 1, 1, 4), m_RendererID(0), m_FilePath("") {
        m_LocalBuffer = new unsigned char[4];
        m_LocalBuffer[0] = r; m_LocalBuffer[1] = g; m_LocalBuffer[2] = b; m_LocalBuffer[3] = a;

        Init();
    }

    OpenGL3Texture::~OpenGL3Texture() {
        GLCALL(glDeleteTextures(1, &m_RendererID));
        if (m_LocalBuffer && m_FilePath == "")
            delete[] m_LocalBuffer;
    }

    void OpenGL3Texture::Bind(unsigned int slot) const {
        GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
        GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
    }

    void OpenGL3Texture::Unbind() const {
        GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
    }
}
