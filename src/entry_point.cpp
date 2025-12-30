// ██████╗ ███████╗███╗   ██╗██████╗ ███████╗██████╗ ██╗      █████╗ ██████╗
// ██╔══██╗██╔════╝████╗  ██║██╔══██╗██╔════╝██╔══██╗██║     ██╔══██╗██╔══██╗
// ██████╔╝█████╗  ██╔██╗ ██║██║  ██║█████╗  ██████╔╝██║     ███████║██████╔╝
// ██╔══██╗██╔══╝  ██║╚██╗██║██║  ██║██╔══╝  ██╔══██╗██║     ██╔══██║██╔══██╗
// ██║  ██║███████╗██║ ╚████║██████╔╝███████╗██║  ██║███████╗██║  ██║██████╔╝
// ╚═╝  ╚═╝╚══════╝╚═╝  ╚═══╝╚═════╝ ╚══════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝

#include "pch.hpp"

#include "opengl.hpp"
#include "spdlog/fmt/bundled/base.h"
#include "window.hpp"
#include "raw_data.hpp"
#include "gui.hpp"
#include "camera.hpp"
#include "shader.hpp"
#include "utils.hpp"
#include "model.hpp"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <ImGuizmo.h>
#include <glad/glad.h>
#include "scenes/resident_evil.hpp"
#include "scene_hierarchy_panel.hpp"

int main(int argc, char **argv)
{
    Lab::CLog::Init();
    Lab::CWindow &window = Lab::CWindow::GetInstance();
    Lab::CCamera camera;
    Lab::CSceneHierarchyPanel &panel = Lab::CSceneHierarchyPanel::GetInstance();

    auto [width, height] = window.GetWindowSizes();
    camera.SetLastPosX(width / 2.0f);
    camera.SetLastPosY(height / 2.0f);
    camera.SetCameraPosition(glm::vec3(0.0f, 0.5f, 0.0f));

#pragma region Debug

    OpenGL::EnableDebug();
    Lab::CShader debugNormalShader({Utils::LAB_BASE_SHADERS_PATH + "gl_debug_normal.vert",
                                    Utils::LAB_BASE_SHADERS_PATH + "gl_debug_normal.frag",
                                    Utils::LAB_BASE_SHADERS_PATH + "gl_debug_normal.geom"});

#pragma endregion Debug

    Lab::SetupImGuiContext(window.GetWindowPointer());

    float deltaTime = 0.0f, lastFrameTime = 0.0f;

    // Scenes
    Lab::CResidentEvilScene &residentEvilScene = Lab::CResidentEvilScene::GetInstance();
    panel.SetSceneContext(residentEvilScene);

    for (; window.IsRunning();) // Main loop
    {
#pragma region Calculate delta time

        const float curFrameTime = static_cast<float>(glfwGetTime());
        deltaTime = curFrameTime - lastFrameTime;
        lastFrameTime = curFrameTime;

#pragma endregion Calculate delta time

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGuizmo::BeginFrame();

        panel.OnImGuiRender();

#define IMGUI_CONTROL_MENU "Control menu"
        ImGui::Begin(IMGUI_CONTROL_MENU, nullptr, ImGuiWindowFlags_NoMove);
        ImGui::SetWindowSize(ImVec2(300.0f, window.GetWindowSizes().second));
        ImGui::SetWindowPos(IMGUI_CONTROL_MENU, ImVec2(0.0f, 0.0f));
        ImGui::End();

#pragma region Resident Evil Scene

        residentEvilScene.OnUpdate(deltaTime, camera, window);

#pragma endregion Resident Evil Scene

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.OnUpdate();
    }

    Lab::ShutdownImGui();

    return 0;
}
