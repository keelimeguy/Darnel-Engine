#include "OpenGL3Lib/Texture.h"

#include <stb_image.h>

void Texture::Init() {
    GLCALL(glGenTextures(1, &m_RendererID));
    GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));

    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture::Texture(const std::string& path)
    : m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    Init();

    if (m_LocalBuffer)
        stbi_image_free(m_LocalBuffer);
}

Texture::Texture(unsigned char* buffer, int width, int height, int bpp)
    : m_RendererID(0), m_FilePath(""), m_LocalBuffer(nullptr), m_Width(width), m_Height(height), m_BPP(bpp)
{
    m_LocalBuffer = new unsigned char[4*width*height];
    for (int i = 0, j = 0; i < 4*width*height; i++) {
        if (bpp < 4 && i%4 >= bpp)
            m_LocalBuffer[i] = (unsigned char)255;
        else
            m_LocalBuffer[i] = buffer[j++];
    }

    Init();
}

Texture::Texture(unsigned char r, unsigned char g, unsigned char b)
    : m_RendererID(0), m_FilePath(""), m_LocalBuffer(nullptr), m_Width(1), m_Height(1), m_BPP(3)
{
    m_LocalBuffer = new unsigned char[4];
    m_LocalBuffer[0] = r; m_LocalBuffer[1] = g; m_LocalBuffer[2] = b; m_LocalBuffer[3] = (unsigned char)255;

    Init();
}

Texture::Texture(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    : m_RendererID(0), m_FilePath(""), m_LocalBuffer(nullptr), m_Width(1), m_Height(1), m_BPP(4)
{
    m_LocalBuffer = new unsigned char[4];
    m_LocalBuffer[0] = r; m_LocalBuffer[1] = g; m_LocalBuffer[2] = b; m_LocalBuffer[3] = a;

    Init();
}

Texture::~Texture() {
    GLCALL(glDeleteTextures(1, &m_RendererID));
    if (m_LocalBuffer && m_FilePath == "")
        delete[] m_LocalBuffer;
}

void Texture::Bind(unsigned int slot) const {
    GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
    GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const {
    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}
