#include "pch.hpp"

#include "horror_scene.hpp"

#include "window/window.hpp"
#include "renderer/model.hpp"
#include "scenes/horror_scene/entities/ground.hpp"

#include <glad/glad.h>

namespace Lab
{

    CHorrorScene::CHorrorScene()
        : m_Window(CWindow::GetInstance()),
          m_Camera(),
          m_Shader(CShader({LAB_BASIC_VERTEX_SHADER_PATH, LAB_BASIC_FRAGMENT_SHADER_PATH})),
          m_OpaqueSceneEntities({std::make_shared<CGround>(CModel("../../../../lab/res/models/ground/ground.fbx"))}),
          m_TransparentSceneEntities({std::make_shared<CSceneEntity>(CModel("../../../../lab/res/models/office_window/office_window.fbx"))})
    {
        m_Camera.SetLastPosX(static_cast<float>(m_Window.GetWidth()) / 2.0f);
        m_Camera.SetLastPosY(static_cast<float>(m_Window.GetHeight()) / 2.0f);
    }

    void CHorrorScene::OnUpdate(float t_DeltaTime)
    {
        m_Shader.Bind();

        for (const std::shared_ptr<CSceneEntity> &sceneEntity : m_OpaqueSceneEntities)
        {
            m_Camera.CameraKeyboardInput(m_Window.GetWindowPointer(), t_DeltaTime);
            m_Camera.CameraMouseMovementInput(m_Window.GetWindowPointer());

            glm::mat4 modelMatrix(1.0f);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f));
            const glm::mat4 viewMatrix = m_Camera.CalculateViewMatrix();
            const glm::mat4 projectionMatrix = m_Camera.CalculatePerspectiveProjectionMatrix(m_Window);

            m_Shader.SetUniformMatrix4fv("u_ModelMatrix", modelMatrix);
            m_Shader.SetUniformMatrix4fv("u_ViewMatrix", viewMatrix);
            m_Shader.SetUniformMatrix4fv("u_ProjectionMatrix", projectionMatrix);

            sceneEntity->m_Model.Draw(m_Shader);
        }

        for (const std::shared_ptr<CSceneEntity> &sceneEntity : m_TransparentSceneEntities)
        {
            m_Camera.CameraKeyboardInput(m_Window.GetWindowPointer(), t_DeltaTime);
            m_Camera.CameraMouseMovementInput(m_Window.GetWindowPointer());

            glm::mat4 modelMatrix(1.0f);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.2f, 0.0f));
            const glm::mat4 viewMatrix = m_Camera.CalculateViewMatrix();
            const glm::mat4 projectionMatrix = m_Camera.CalculatePerspectiveProjectionMatrix(m_Window);

            m_Shader.SetUniformMatrix4fv("u_ModelMatrix", modelMatrix);
            m_Shader.SetUniformMatrix4fv("u_ViewMatrix", viewMatrix);
            m_Shader.SetUniformMatrix4fv("u_ProjectionMatrix", projectionMatrix);

            sceneEntity->m_Model.Draw(m_Shader);
        }
    }

} // namespace Lab
