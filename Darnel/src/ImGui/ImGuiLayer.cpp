#include "ImGuiLayer.h"
#include "Application.h"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

namespace darnel {

    void ImGuiLayer::OnAttach() {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;  // Enable Multi-Viewport
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Tweak window style for consistency with viewports
        ImGuiStyle &style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        auto wnd = Application::Get()->GetWindow().lock();
        DARNEL_ASSERT(wnd, "No active window");
        GLFWwindow *window = static_cast<GLFWwindow *>(wnd->GetNativeWindow());

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");

    }

    void ImGuiLayer::OnDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::Begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End() {
        ImGuiIO &io = ImGui::GetIO();

        auto wnd = Application::Get()->GetWindow().lock();
        DARNEL_ASSERT(wnd, "No active window");

        io.DisplaySize = ImVec2(wnd->GetWidth(), wnd->GetHeight());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
}
