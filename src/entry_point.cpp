// ██████╗ ███████╗███╗   ██╗██████╗ ███████╗██████╗ ██╗      █████╗ ██████╗
// ██╔══██╗██╔════╝████╗  ██║██╔══██╗██╔════╝██╔══██╗██║     ██╔══██╗██╔══██╗
// ██████╔╝█████╗  ██╔██╗ ██║██║  ██║█████╗  ██████╔╝██║     ███████║██████╔╝
// ██╔══██╗██╔══╝  ██║╚██╗██║██║  ██║██╔══╝  ██╔══██╗██║     ██╔══██║██╔══██╗
// ██║  ██║███████╗██║ ╚████║██████╔╝███████╗██║  ██║███████╗██║  ██║██████╔╝
// ╚═╝  ╚═╝╚══════╝╚═╝  ╚═══╝╚═════╝ ╚══════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝

#include "pch.hpp"

#include "window.hpp"
#include "raw_data.hpp"
#include "gui.hpp"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <glad/glad.h>

int main(int argc, char **argv)
{
    Lab::CLog::Init();
    Lab::CWindow &window = Lab::CWindow::GetInstance();

    Lab::SetupImGuiContext(window.GetWindowPointer());

    for (; window.IsRunning();) // Main loop
    {

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Control menu", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::SetWindowSize(ImVec2(300.0f, 500.0f));
        ImGui::SetWindowPos("Control menu", ImVec2(0.0f, 0.0f));

#pragma region Basic lighting scene

        if (ImGui::CollapsingHeader("Basic lighting scene"))
        {
            static bool isRender = false;
            if (ImGui::Button("Start scene"))
            {
                isRender = !isRender;
            }

            if (isRender)
            {
                LAB_INFO_LOG("Rendering basic lighting scene");
                glClear(GL_COLOR_BUFFER_BIT);
                glClearColor(0.2f, 1.0f, 0.2f, 1.0f);
            }
            else
            {
                glClear(GL_COLOR_BUFFER_BIT);
                glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            }
        }
        else
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        }

#pragma endregion Basic lighting scene

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.OnUpdate();
    }

    Lab::ShutdownImGui();

    return 0;
}
