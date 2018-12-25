#include "OpenGL3Framework.h"
#include "OpenGL3Window.h"
#include "OpenGL3Sprite.h"

#include "OpenGL3Renderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

const char* glsl_version = "#version 150";

namespace darnel {
    Window* OpenGL3Framework::Init(int width, int height, std::string name) {
        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit())
            return nullptr;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // GLFW 3.2+

        Window* window = CreateWindow(width, height, name);
        window->MakeActive();

        if (glewInit())
            return nullptr;

        GLCALL(std::cout << glGetString(GL_VERSION) << std::endl);
        GLCALL(glEnable(GL_BLEND));
        GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        return window;
    }

    void OpenGL3Framework::Terminate() {
        OpenGL3Sprite::SpriteContext::m_ib = nullptr;
        OpenGL3Sprite::SpriteContext::m_shader = nullptr;
        glfwTerminate();
    }

    Window* OpenGL3Framework::CreateWindow(int width, int height, std::string name) {
        m_windows.push_back(std::make_unique<OpenGL3Window>(width, height, name));
        if (!m_windows.back()->IsValid()) {
            m_windows.pop_back();
            return nullptr;
        }
        return m_windows.back().get();
    }

    bool OpenGL3Framework::WindowLoop(Window* window) {
        glfwSwapBuffers(((OpenGL3Window*)window)->m_window);
        glfwPollEvents();

        return glfwWindowShouldClose(((OpenGL3Window*)window)->m_window);
    }

    void OpenGL3Framework::ImGuiInit(Window* window) {
        ImGui_ImplGlfw_InitForOpenGL(((OpenGL3Window*)window)->m_window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    void OpenGL3Framework::ImGuiNewFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
    }

    void OpenGL3Framework::ImGuiRenderDrawData(ImDrawData* drawData) {
        ImGui_ImplOpenGL3_RenderDrawData(drawData);
    }

    void OpenGL3Framework::ImGuiShutdown() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
    }
}
