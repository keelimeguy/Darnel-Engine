#pragma once

#include "Core.h"
#include "Texture.h"

namespace darnel {
    class Sprite;

    class SpriteSheet {
    public:
        SpriteSheet(std::string path, int numTilesX, int numTilesY);
        ~SpriteSheet();

        std::shared_ptr<Texture> GrabTexture(int t_x, int t_y);
        std::shared_ptr<Texture> GrabTexture(int t_x, int t_y, int t_width, int t_height);

        int GetWidth() { return m_width; }
        int GetHeight() { return m_height; }

    private:
        unsigned char *m_LocalBuffer;
        int m_width, m_height, m_BPP;
        int m_tileWidth, m_tileHeight;
    };
}
