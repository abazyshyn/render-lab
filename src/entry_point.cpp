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

void OceanSceneOnUpdate(bool isOceanSceneRendering, Lab::CCamera &camera, Lab::CWindow &window,
                        Lab::CShader &gridShader, Lab::CShader &oceanShader, Lab::CShader &debugNormalShader,
                        Lab::CModel &oceanModel, float deltaTime);

int main(int argc, char **argv)
{
    Lab::CLog::Init();
    Lab::CWindow &window = Lab::CWindow::GetInstance();
    Lab::CCamera camera;

    auto [width, height] = window.GetWindowSizes();
    camera.SetLastPosX(width / 2.0f);
    camera.SetLastPosY(height / 2.0f);
    camera.SetCameraPosition(glm::vec3(0.0f, 1.0f, 0.0f));

#pragma region Debug

    OpenGL::EnableDebug();
    Lab::CShader debugNormalShader({Utils::LAB_BASE_SHADERS_PATH + "gl_debug_normal.vert",
                                    Utils::LAB_BASE_SHADERS_PATH + "gl_debug_normal.frag",
                                    Utils::LAB_BASE_SHADERS_PATH + "gl_debug_normal.geom"});

#pragma endregion Debug

    Lab::SetupImGuiContext(window.GetWindowPointer());

#pragma region Ocean scene setup

    Lab::CShader gridShader({Utils::LAB_BASE_SHADERS_PATH + "gl_grid.vert", Utils::LAB_BASE_SHADERS_PATH + "gl_grid.frag"});
    Lab::CShader oceanShader({Utils::LAB_BASE_SHADERS_PATH + "gl_ocean.vert", Utils::LAB_BASE_SHADERS_PATH + "gl_ocean.frag"});
    Lab::CModel oceanModel(Utils::LAB_BASE_MODELS_PATH + "ocean_scene/untitled.glb");

#pragma endregion Ocean scene setup

    float deltaTime = 0.0f, lastFrameTime = 0.0f;

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

        static bool isOceanSceneRendering = false;

#define IMGUI_CONTROL_MENU "Control menu"
        ImGui::Begin(IMGUI_CONTROL_MENU, 0, ImGuiWindowFlags_NoMove);
        ImGui::SetWindowSize(ImVec2(ImGui::GetWindowSize().x ? ImGui::GetWindowSize().x : 300.0f, window.GetWindowSizes().second));
        ImGui::SetWindowPos(IMGUI_CONTROL_MENU, ImVec2(0.0f, 0.0f));

#pragma region Ocean scene

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

        OceanSceneOnUpdate(isOceanSceneRendering, camera, window, gridShader, oceanShader, debugNormalShader, oceanModel, deltaTime);

#pragma endregion Ocean scene

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.OnUpdate();
    }

    Lab::ShutdownImGui();

    return 0;
}

void OceanSceneOnUpdate(bool isOceanSceneRendering, Lab::CCamera &camera, Lab::CWindow &window,
                        Lab::CShader &gridShader, Lab::CShader &oceanShader, Lab::CShader &debugNormalShader,
                        Lab::CModel &oceanModel, float deltaTime)
{
    if (!isOceanSceneRendering)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        return;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(0.2f, 1.0f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_CLAMP);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    camera.CameraKeyboardInput(window.GetWindowPointer(), deltaTime);
    camera.CameraMouseMovementInput(window.GetWindowPointer());

    glm::mat4 modelMatrix(1.0f);
    glm::mat4 viewMatrix = camera.CalculateViewMatrix();
    // glm::mat3 normalMatrix = glm::transpose(glm::inverse(modelMatrix));
    glm::mat4 projectionMatrix = camera.CalculatePerspectiveProjectionMatrix(window);

    // gridShader.Bind();
    // gridShader.SetUniform3fv("u_CameraWorldPos", camera.GetCameraPos());
    // gridShader.SetUniformMatrix4fv("u_ViewMatrix", viewMatrix);
    // gridShader.SetUniformMatrix4fv("u_ProjectionMatrix", projectionMatrix);

    // glDrawArrays(GL_TRIANGLES, 0, 6);

    oceanShader.Bind();

    // modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -7.0f, 0.0f));
    //  modelMatrix = glm::scale(modelMatrix, glm::vec3(100.0f, 50.0f, 100.0f));
    glm::vec3 lightDirWorld = glm::normalize(glm::vec3(0.0f, -1.0, -3.0f)); // toward the surface
    // glm::vec3 lightDirView = glm::mat3(modelMatrix) * lightDirWorld;

    oceanShader.SetUniform1f("u_Time", static_cast<float>(glfwGetTime()));
    oceanShader.SetUniform3fv("u_LightDirection", lightDirWorld); // Rename it
    // oceanShader.SetUniformMatrix3fv("u_NormalMatrix", normalMatrix);
    oceanShader.SetUniform3fv("u_CameraPos", camera.GetCameraPos());
    oceanShader.SetUniformMatrix4fv("u_ModelMatrix", modelMatrix);
    oceanShader.SetUniformMatrix4fv("u_ViewMatrix", viewMatrix);
    oceanShader.SetUniformMatrix4fv("u_ProjectionMatrix", projectionMatrix);

    oceanModel.Draw(oceanShader);

    // debugNormalShader.Bind();

    // debugNormalShader.SetUniformMatrix4fv("u_ModelMatrix", modelMatrix);
    // debugNormalShader.SetUniformMatrix4fv("u_ViewMatrix", camera.CalculateViewMatrix());
    // debugNormalShader.SetUniformMatrix4fv("u_ProjectionMatrix", camera.CalculatePerspectiveProjectionMatrix(window));

    // oceanModel.Draw(debugNormalShader);
}
