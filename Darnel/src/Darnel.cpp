#include "OpenGL3Lib/Renderer.h"
#include "Sprite.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

static GLFWwindow* window;
const char* glsl_version = "#version 150";

namespace darnel {
    int DarnelInit() {
        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit())
            return -1;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // GLFW 3.2+

        window = glfwCreateWindow(640, 480, "Darnel_Testing", NULL, NULL);
        if (window == NULL) {
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        if (glewInit())
            return -1;

        GLCALL(std::cout << glGetString(GL_VERSION) << std::endl);
        GLCALL(glEnable(GL_BLEND));
        GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        return 0;
    }

    void DarnelTerminate() {
        Sprite::SpriteContext::m_ib = nullptr;
        Sprite::SpriteContext::m_shader = nullptr;
        glfwTerminate();
    }

    void DarnelClear(float f0, float f1, float f2, float f3) {
        GLCALL(glClearColor(f0, f1, f2, f3));
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));
    }

    bool DarnelLoopDone() {
        glfwSwapBuffers(window);
        glfwPollEvents();

        return glfwWindowShouldClose(window);
    }

    void ImGui_Darnel_Init() {
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    void ImGui_Darnel_NewFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
    }

    void ImGui_Darnel_RenderDrawData(ImDrawData* drawData) {
        ImGui_ImplOpenGL3_RenderDrawData(drawData);
    }

    void ImGui_Darnel_Shutdown() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
    }
}
