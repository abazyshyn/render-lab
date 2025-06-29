#include "pch.hpp"

#include "scene.hpp"

#include "window/window.hpp"
#include "renderer/model.hpp"
#include "scene_entities/scene_1/ground/ground.hpp"

#include <glad/glad.h>

namespace Lab
{

    CScene &CScene::GetInstance()
    {
        static CScene s_Instance;
        return s_Instance;
    }

    void CScene::OnUpdate(float t_DeltaTime)
    {
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f));
            const glm::mat4 viewMatrix = m_Camera.CalculateViewMatrix();
            const glm::mat4 projectionMatrix = m_Camera.CalculatePerspectiveProjectionMatrix(m_Window);

            m_Shader.SetUniformMatrix4fv("u_ModelMatrix", modelMatrix);
            m_Shader.SetUniformMatrix4fv("u_ViewMatrix", viewMatrix);
            m_Shader.SetUniformMatrix4fv("u_ProjectionMatrix", projectionMatrix);

            sceneEntity->m_Model.Draw(m_Shader);
        }

        m_Shader.UnBind();
    }

    CScene::CScene()
        : m_Window(CWindow::GetInstance()),
          m_Shader({LAB_BASIC_VERTEX_SHADER_PATH, LAB_BASIC_FRAGMENT_SHADER_PATH}),
          m_OpaqueSceneEntities({std::make_shared<CGround>(CModel("../../../../lab/res/models/ground/ground.fbx"))}),
          m_TransparentSceneEntities({std::make_shared<CSceneEntity>(CModel("../../../../lab/res/models/office_window/office_window.fbx"))})
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_DEPTH_CLAMP);
        glEnable(GL_BLEND);

        glDepthFunc(GL_LESS);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        m_Camera.SetLastPosX(static_cast<float>(m_Window.GetWidth()) / 2.0f);
        m_Camera.SetLastPosY(static_cast<float>(m_Window.GetHeight()) / 2.0f);
    }

} // namespace Lab