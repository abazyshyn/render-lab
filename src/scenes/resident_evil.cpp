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

    CResidentEvilScene::CResidentEvilScene()
        : // m_DiningRoomModel(Utils::LAB_BASE_MODELS_PATH + "resident_evil_scene/dining_room/scene.gltf"),
          m_DiningRoomShader({Utils::LAB_BASE_SHADERS_PATH + "gl_dining_room.vert",
                              Utils::LAB_BASE_SHADERS_PATH + "gl_dining_room.frag"}),
          m_Framebuffer(1920, 1080),
          m_GuizmoOperation(-1)
    {
        m_Models.emplace_back(Utils::LAB_BASE_MODELS_PATH + "resident_evil_scene/dining_room/scene.gltf");
    }

    CResidentEvilScene::CResidentEvilScene(CResidentEvilScene &&source) noexcept
        : m_DiningRoomShader(std::move(source.m_DiningRoomShader)),
          m_Framebuffer(std::move(source.m_Framebuffer)),
          m_GuizmoOperation(source.m_GuizmoOperation)
    {
        for (CModel &model : source.m_Models)
        {
            m_Models.emplace_back(std::move(model));
        }
    }

    CResidentEvilScene &CResidentEvilScene::operator=(CResidentEvilScene &&source) noexcept
    {
        if (this == &source)
        {
            return *this;
        }

        for (CModel &model : source.m_Models)
        {
            m_Models.emplace_back(std::move(model));
        }

        m_DiningRoomShader = std::move(source.m_DiningRoomShader);
        m_Framebuffer = std::move(source.m_Framebuffer);
        m_GuizmoOperation = source.m_GuizmoOperation;

        return *this;
    }

    void CResidentEvilScene::OnUpdate(float deltaTime, CCamera &camera, CWindow &window)
    {
        m_DiningRoomShader.Bind();

        camera.CameraKeyboardInput(window.GetWindowPointer(), deltaTime);

        // TODO: Hack
        if (glfwGetKey(window.GetWindowPointer(), GLFW_KEY_F))
        {
            camera.CameraMouseMovementInput(window.GetWindowPointer());
        }
        else
        {
            double x = 0.0, y = 0.0;
            glfwGetCursorPos(window.GetWindowPointer(), &x, &y);
            camera.SetLastPosX((float)x);
            camera.SetLastPosY((float)y);
        }

        // Iteration over the models
        for (CModel &model : m_Models)
        {
            glm::mat4 modelMatrix = model.GetModelMatrix();
            glm::mat4 viewMatrix = camera.CalculateViewMatrix();
            // glm::mat3 normalMatrix = glm::transpose(glm::inverse(modelMatrix));
            glm::mat4 projectionMatrix = camera.CalculatePerspectiveProjectionMatrix(window);

#define WINDOW "Scene"
            ImGui::Begin(WINDOW);
            const float windowWidth = window.GetWindowSizes().first - 300.0f;
            const float windowHeight = window.GetWindowSizes().second;
            ImGui::SetWindowSize(ImVec2(windowWidth, windowHeight));
            ImGui::SetWindowPos(WINDOW, ImVec2(300.0f, 0.0f));

            ImGui::BeginChild("SceneRender");

            m_DiningRoomShader.SetUniformMatrix4fv("u_ModelMatrix", modelMatrix);
            m_DiningRoomShader.SetUniformMatrix4fv("u_ViewMatrix", viewMatrix);
            m_DiningRoomShader.SetUniformMatrix4fv("u_ProjectionMatrix", projectionMatrix);

            m_Framebuffer.OnUpdate(static_cast<uint32_t>(windowWidth), static_cast<uint32_t>(windowHeight));
            m_Framebuffer.Bind();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            glClearColor(0.2f, 1.0f, 0.2f, 1.0f);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_DEPTH_CLAMP);
            glDepthFunc(GL_LESS);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            model.Draw(m_DiningRoomShader);

            ImGui::Image((ImTextureID)m_Framebuffer.GetColorBuffer(), ImGui::GetWindowSize(), ImVec2(0, 1), ImVec2(1, 0));

            DrawModelGuizmo(window, model, modelMatrix, viewMatrix, projectionMatrix);

            ImGui::EndChild();

            ImGui::End();

            m_Framebuffer.UnBind();

            glClearColor(0.2f, 1.0f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }
    }

    void CResidentEvilScene::DrawModelGuizmo(CWindow &window, CModel &model, glm::mat4 &modelMatrix, glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix)
    {
        // TODO: ImGuizmo operation change hack
        if (glfwGetKey(window.GetWindowPointer(), GLFW_KEY_1))
        {
            m_GuizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
        }
        else if (glfwGetKey(window.GetWindowPointer(), GLFW_KEY_2))
        {
            m_GuizmoOperation = ImGuizmo::OPERATION::ROTATE;
        }
        else if (glfwGetKey(window.GetWindowPointer(), GLFW_KEY_3))
        {
            m_GuizmoOperation = ImGuizmo::OPERATION::SCALE;
        }

        // Guizmo
        if (m_GuizmoOperation != -1)
        {
            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist();
            auto [windowWidth, windowHeight] = window.GetWindowSizes();
            ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);
            ImGuizmo::Manipulate(glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix),
                                 static_cast<ImGuizmo::OPERATION>(m_GuizmoOperation), ImGuizmo::LOCAL, glm::value_ptr(modelMatrix));

            if (ImGuizmo::IsUsing())
            {
                model.SetModelMatrix(modelMatrix);
            }
        }
    }

    void CResidentEvilScene::SetupScene()
    {
    }

} // namespace Lab
