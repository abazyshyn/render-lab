// ██████╗ ███████╗███╗   ██╗██████╗ ███████╗██████╗ ██╗      █████╗ ██████╗
// ██╔══██╗██╔════╝████╗  ██║██╔══██╗██╔════╝██╔══██╗██║     ██╔══██╗██╔══██╗
// ██████╔╝█████╗  ██╔██╗ ██║██║  ██║█████╗  ██████╔╝██║     ███████║██████╔╝
// ██╔══██╗██╔══╝  ██║╚██╗██║██║  ██║██╔══╝  ██╔══██╗██║     ██╔══██║██╔══██╗
// ██║  ██║███████╗██║ ╚████║██████╔╝███████╗██║  ██║███████╗██║  ██║██████╔╝
// ╚═╝  ╚═╝╚══════╝╚═╝  ╚═══╝╚═════╝ ╚══════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝

#include "opengl.hpp"
#include "pch.hpp"

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
#include <glad/glad.h>

int main(int argc, char **argv)
{
    Lab::CLog::Init();
    Lab::CWindow &window = Lab::CWindow::GetInstance();
    Lab::CCamera camera;

    auto [width, height] = window.GetWindowSizes();
    camera.SetLastPosX(width / 2.0f);
    camera.SetLastPosY(height / 2.0f);
    camera.SetCameraPosition(glm::vec3(0.0f, 1.0f, 0.0f));

    OpenGL::EnableDebug();
    Lab::SetupImGuiContext(window.GetWindowPointer());

#pragma region Ocean scene setup

    Lab::CShader gridShader({Utils::LAB_BASE_SHADERS_PATH + "gl_grid.vert", Utils::LAB_BASE_SHADERS_PATH + "gl_grid.frag"});
    Lab::CShader oceanShader({Utils::LAB_BASE_SHADERS_PATH + "gl_ocean.vert", Utils::LAB_BASE_SHADERS_PATH + "gl_ocean.frag"});
    Lab::CModel oceanModel(Utils::LAB_BASE_MODELS_PATH + "ocean_scene/ocean.glb");

#pragma endregion Ocean scene setup

    for (; window.IsRunning();) // Main loop
    {
#pragma region Calculate delta time

        static float deltaTime = 0.0f, lastFrameTime = 0.0f;

        const float curFrameTime = static_cast<float>(glfwGetTime());
        deltaTime = curFrameTime - lastFrameTime;
        lastFrameTime = curFrameTime;

#pragma endregion Calculate delta time

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Control menu", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::SetWindowSize(ImVec2(300.0f, window.GetWindowSizes().second));
        ImGui::SetWindowPos("Control menu", ImVec2(0.0f, 0.0f));

#pragma region Ocean scene

        static bool isOceanSceneRendering = false;
        if (ImGui::CollapsingHeader("Ocean scene"))
        {
            if (ImGui::Button(!isOceanSceneRendering ? "Start rendering scene" : "Stop rendering scene"))
            {
                isOceanSceneRendering = !isOceanSceneRendering;
            }
        }
        else
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        }

        if (isOceanSceneRendering)
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            glClearColor(0.2f, 1.0f, 0.2f, 1.0f);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_DEPTH_CLAMP);
            glDepthFunc(GL_LESS);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            camera.CameraKeyboardInput(window.GetWindowPointer(), deltaTime);
            camera.CameraMouseMovementInput(window.GetWindowPointer());

            gridShader.Bind();
            gridShader.SetUniform3fv("u_CameraWorldPos", camera.GetCameraPos());
            gridShader.SetUniformMatrix4fv("u_ViewMatrix", camera.CalculateViewMatrix());
            gridShader.SetUniformMatrix4fv("u_ProjectionMatrix", camera.CalculatePerspectiveProjectionMatrix(window));

            glDrawArrays(GL_TRIANGLES, 0, 6);

            oceanShader.Bind();

            glm::mat4 modelMatrix(1.0f);

            oceanShader.SetUniformMatrix4fv("u_ModelMatrix", modelMatrix);
            oceanShader.SetUniformMatrix4fv("u_ViewMatrix", camera.CalculateViewMatrix());
            oceanShader.SetUniformMatrix4fv("u_ProjectionMatrix", camera.CalculatePerspectiveProjectionMatrix(window));

            glDisable(GL_DEPTH_TEST);
            oceanModel.Draw(oceanShader);
        }
        else
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        }

#pragma endregion Ocean scene

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.OnUpdate();
    }

    Lab::ShutdownImGui();

    return 0;
}
