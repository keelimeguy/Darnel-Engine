#include "OpenGL3Framework.h"
#include "OpenGL3Window.h"
#include "OpenGL3Sprite.h"
#include "OpenGL3Texture.h"

#include "OpenGL3Renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Event.h"
#include "WindowEvent.h"

#include <string>
#include <iostream>
#include <functional>
#include <algorithm>

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
        if (!window) return nullptr;

        if (glewInit())
            return nullptr;

        GLCALL(std::cout << glGetString(GL_VERSION) << std::endl);
        GLCALL(glEnable(GL_BLEND));
        GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        return window;
    }

    void OpenGL3Framework::Terminate() {
        OpenGL3Sprite::SpriteContext::s_ib = nullptr;
        OpenGL3Sprite::SpriteContext::s_shader = nullptr;
        m_Windows.clear();
        glfwTerminate();
    }

    void OpenGL3Framework::PollEvents() {
        glfwPollEvents();
    }

    Window* OpenGL3Framework::CreateWindow(int width, int height, std::string name, bool forceActive) {
        m_Windows.push_back(std::make_unique<OpenGL3Window>(width, height, name));
        Window* newWindow = m_Windows.back().get();
        if (!newWindow->IsValid()) {
            m_Windows.pop_back();
            return nullptr;
        }
        newWindow->SetEventCallback(std::bind(&OpenGL3Framework::OnEvent, this, std::placeholders::_1, newWindow));
        if (forceActive) {
            m_ActiveWindow = newWindow;
            newWindow->MakeActiveContext();
        }
        return newWindow;
    }

    Window* OpenGL3Framework::GetWindow(std::string name) {
        for(auto const& window: m_Windows)
            if (window->GetName() == name) return window.get();
        return nullptr;
    }

    void OpenGL3Framework::OnEvent(Event& e, Window* window) {
        std::cout << "[" << window->GetName() << "] " << e.ToString() << std::endl << std::flush;

        EventDispatcher dispatcher(e);
        if (dispatcher.Dispatch<WindowCloseEvent>(std::bind(&OpenGL3Framework::OnWindowClose, this, std::placeholders::_1, window)));
        else if (dispatcher.Dispatch<WindowFocusEvent>(std::bind(&OpenGL3Framework::OnWindowFocus, this, std::placeholders::_1, window)));
    }

    bool OpenGL3Framework::OnWindowFocus(WindowFocusEvent& e, Window* window) {
        m_ActiveWindow = window;
        window->MakeActiveContext();
        return true;
    }

    bool OpenGL3Framework::OnWindowClose(WindowCloseEvent& e, Window* window) {
        // We need a context still active during termination,
        // so don't delete the window if it is the last one
        if (m_Windows.size() == 1 && m_Windows[0].get() == window) {
            m_Running = false;

        } else {
            m_Windows.erase(std::find_if(m_Windows.begin(), m_Windows.end(),
                [window](auto& wnd) { return wnd.get() == window; }
            ));
            m_ActiveWindow = m_Windows.back().get();
        }
        return true;
    }

    std::shared_ptr<Sprite> OpenGL3Framework::MakeSprite(float x, float y, float width, float height, std::shared_ptr<Texture> texture) {
        return std::make_shared<OpenGL3Sprite>(x, y, width, height, texture);
    }

    std::shared_ptr<Texture> OpenGL3Framework::MakeTexture(const std::string& path) {
        return std::make_shared<OpenGL3Texture>(path);
    }

    std::shared_ptr<Texture> OpenGL3Framework::MakeTexture(unsigned char* buffer, int width, int height, int bpp) {
        return std::make_shared<OpenGL3Texture>(buffer, width, height, bpp);
    }

    std::shared_ptr<Texture> OpenGL3Framework::MakeTexture(unsigned char r, unsigned char g, unsigned char b) {
        return std::make_shared<OpenGL3Texture>(r, g, b);
    }

    std::shared_ptr<Texture> OpenGL3Framework::MakeTexture(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        return std::make_shared<OpenGL3Texture>(r, g, b, a);
    }

    void OpenGL3Framework::ImGuiInit() {
        ImGui_ImplGlfw_InitForOpenGL(((OpenGL3Window*)m_ActiveWindow)->m_Window, true);
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
