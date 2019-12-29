#include "OpenGL3Renderer.h"
#include "Sprite.h"
#include "Renderer.h"

namespace darnel {
    static void glfw_error_callback(int error, const char *description) {
        fprintf(stderr, "Glfw Error %d: %s\n", error, description);
    }

    const char *glsl_version = "#version 150";

    void GLClearError() {
        while (glGetError() != GL_NO_ERROR);
    }

    bool GLLogCall(const char *function, const char *file, int line) {
        bool ret = true;
        while (GLenum error = glGetError()) {
            std::cout << "[OpenGL Error] (0x" << std::hex << error << "):"
                      << function << " " << file << ":" << line << std::endl;
            ret = false;
        }
        return ret;
    }

    GLFWwindow *OpenGL3Renderer::Init(std::string name, unsigned int width, unsigned int height) {
        ASSERT(glfwInit());
        glfwSetErrorCallback(glfw_error_callback);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // GLFW 3.2+

        auto window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
        ASSERT(window);

        glfwMakeContextCurrent(window);

        ASSERT(!glewInit());
        GLCALL(std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl);
        GLCALL(std::cout << "GPU: " << glGetString(GL_RENDERER) << std::endl);
        GLCALL(glEnable(GL_BLEND));
        GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        return window;
    }
}

namespace darnel {
    void OpenGL3RendererAPI::Init() {
    }

    void OpenGL3RendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    }

    void OpenGL3RendererAPI::SetClearColor(float f0, float f1, float f2, float f3) {
        GLCALL(glClearColor(f0, f1, f2, f3));
    }

    void OpenGL3RendererAPI::SetClearColor(const glm::vec4 &color) {
        GLCALL(glClearColor(color.r, color.g, color.b, color.a));
    }

    void OpenGL3RendererAPI::Clear() {
        GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }

    void OpenGL3RendererAPI::Draw(const VertexArray &va, const IndexBuffer &ib) {
        va.Bind();
        ib.Bind();
        GLCALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
    }

    void OpenGL3Renderer::BeginScene() {
    }

    void OpenGL3Renderer::EndScene() {
    }

    void OpenGL3Renderer::Terminate(std::vector<std::shared_ptr<Window>> *windows) {
        if (windows) {
            windows->clear();
        }
        glfwTerminate();
    }
}
