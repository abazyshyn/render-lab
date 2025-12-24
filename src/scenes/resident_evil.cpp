#include "pch.hpp"

#include "resident_evil.hpp"
#include "utils.hpp"
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <ImGuizmo.h>

namespace Lab
{

    void CResidentEvilScene::SetupScene()
    {
    }

    void CResidentEvilScene::OnUpdate(float deltaTime, CCamera &camera, CWindow &window)
    {

        m_DiningRoomShader.Bind();

        camera.CameraKeyboardInput(window.GetWindowPointer(), deltaTime);
        camera.CameraMouseMovementInput(window.GetWindowPointer());

        glm::mat4 modelMatrix(1.0f);
        glm::mat4 viewMatrix = camera.CalculateViewMatrix();
        // glm::mat3 normalMatrix = glm::transpose(glm::inverse(modelMatrix));
        glm::mat4 projectionMatrix = camera.CalculatePerspectiveProjectionMatrix(window);

        m_DiningRoomShader.SetUniformMatrix4fv("u_ModelMatrix", modelMatrix);
        m_DiningRoomShader.SetUniformMatrix4fv("u_ViewMatrix", viewMatrix);
        m_DiningRoomShader.SetUniformMatrix4fv("u_ProjectionMatrix", projectionMatrix);

#define WINDOW "Scene"
        ImGui::Begin(WINDOW);
        const float windowWidth = window.GetWindowSizes().first - 300.0f;
        const float windowHeight = window.GetWindowSizes().second;
        ImGui::SetWindowSize(ImVec2(windowWidth, windowHeight));
        ImGui::SetWindowPos(WINDOW, ImVec2(300.0f, 0.0f));

        // Guizmo
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();
        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);
        ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix),
                             ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::LOCAL, glm::value_ptr(modelMatrix));

        CFramebuffer framebuffer(static_cast<uint32_t>(windowWidth), static_cast<uint32_t>(windowHeight));
        framebuffer.Bind();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(0.2f, 1.0f, 0.2f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_DEPTH_CLAMP);
        glDepthFunc(GL_LESS);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        m_DiningRoomModel.Draw(m_DiningRoomShader);

        ImGui::BeginChild("SceneRender");

        ImGui::Image((ImTextureID)framebuffer.GetColorBuffer(), ImGui::GetWindowSize(), ImVec2(0, 1), ImVec2(1, 0));

        ImGui::EndChild();

        ImGui::End();

        framebuffer.UnBind();
        glClearColor(0.2f, 1.0f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    CResidentEvilScene::CResidentEvilScene()
        : m_DiningRoomModel(Utils::LAB_BASE_MODELS_PATH + "resident_evil_scene/dining_room/scene.gltf"),
          m_DiningRoomShader({Utils::LAB_BASE_SHADERS_PATH + "gl_dining_room.vert",
                              Utils::LAB_BASE_SHADERS_PATH + "gl_dining_room.frag"})
    {
    }

} // namespace Lab
