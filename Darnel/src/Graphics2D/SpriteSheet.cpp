#include "Darnel.h"

#include "SpriteSheet.h"
#include "Texture.h"

#include <stb_image.h>

namespace darnel {
    SpriteSheet::SpriteSheet(std::string path, int numTilesX, int numTilesY) {
        stbi_set_flip_vertically_on_load(1);
        m_LocalBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, 4);

        m_tileWidth = m_width / numTilesX;
        m_tileHeight = m_height / numTilesY;
    }

    SpriteSheet::~SpriteSheet() {
        if (m_LocalBuffer) stbi_image_free(m_LocalBuffer);
    }

    std::shared_ptr<Texture> SpriteSheet::GrabTexture(int t_x, int t_y) {
        if (m_width < (t_x + 1)*m_tileWidth || m_height < (t_y + 1)*m_tileHeight) return nullptr;

        std::vector<unsigned char> buffer(4 * m_tileWidth * m_tileHeight);

        for (int idx = 0, j = t_y * m_tileHeight; j < (t_y + 1)*m_tileHeight; ++j) {
            for (int i = t_x * m_tileWidth; i < (t_x + 1)*m_tileWidth; ++i, idx += 4) {
                for (int k = 0; k < 4; ++k) {
                    buffer[idx + k] = m_LocalBuffer[4 * (i + j * m_width) + k];
                }
            }
        }

        return Texture::Create(&buffer[0], m_tileWidth, m_tileHeight, 4);
    }

    std::shared_ptr<Texture> SpriteSheet::GrabTexture(int t_x, int t_y, int t_width, int t_height) {
        if (m_width < t_x + t_width || m_height < t_y + t_height) return nullptr;

        std::vector<unsigned char> buffer(4 * m_tileWidth * m_tileHeight);

        for (int idx = 0, j = t_y; j < t_y + t_height; ++j) {
            for (int i = t_x; i < t_x + t_width; ++i, idx += 4) {
                for (int k = 0; k < 4; ++k) {
                    buffer[idx + k] = m_LocalBuffer[4 * (i + j * m_width) + k];
                }
            }
        }

        return Texture::Create(&buffer[0], t_width, t_height, 4);
    }
}
