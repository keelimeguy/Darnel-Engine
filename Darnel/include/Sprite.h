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
    static std::unordered_map<std::string, std::weak_ptr<SpriteContext>> m_contextCache;

    glm::vec3 m_translation;
    std::shared_ptr<Texture> m_texture;
    std::shared_ptr<SpriteContext> m_context;
};
