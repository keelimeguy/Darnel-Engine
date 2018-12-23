#include "Renderer.h"
#include "Sprite.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

static GLFWwindow* window;

int darnelInit() {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return -1;

    const char* glsl_version = "#version 150";
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

void darnelTerminate() {
    Sprite::SpriteContext::m_ib = nullptr;
    Sprite::SpriteContext::m_shader = nullptr;
    glfwTerminate();
}

void darnelClear(float f0, float f1, float f2, float f3) {
    GLCALL(glClearColor(f0, f1, f2, f3));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}

bool darnelLoopDone() {
    glfwSwapBuffers(window);
    glfwPollEvents();

    return glfwWindowShouldClose(window);
}
