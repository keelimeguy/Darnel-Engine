#pragma once

#include <glm/glm.hpp>

#include <memory>
#include <string>
#include <unordered_map>

class VertexArray;
class VertexBuffer;
class IndexBuffer;
class Shader;
class Texture;

class Sprite {
public:
    Sprite(float x, float y, float width, float height, const std::string& path);
    Sprite(float x, float y, float width, float height, unsigned char r, unsigned char g, unsigned char b);
    Sprite(float x, float y, float width, float height, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    Sprite(float x, float y, float width, float height, unsigned char* buffer, int bwidth, int bheight, int bpp);
    ~Sprite();

    void Draw(const glm::mat4& proj_view);

    class SpriteContext {
    public:
        static std::unique_ptr<IndexBuffer> m_ib;
        static std::unique_ptr<Shader> m_shader;

        SpriteContext(float width, float height);

        float m_width, m_height;
        std::unique_ptr<VertexArray> m_va;
        std::unique_ptr<VertexBuffer> m_vb;
    };

private:
    void InitContext(float width, float height);

    static std::unordered_map<std::string, std::weak_ptr<SpriteContext>> m_contextCache;

    glm::vec3 m_translation;
    std::shared_ptr<Texture> m_texture;
    std::shared_ptr<SpriteContext> m_context;
};
