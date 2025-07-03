#include "pch.hpp"

#include "horror_scene.hpp" // target

#include "window/window.hpp"
#include "scenes/skybox/skybox.hpp"
#include "renderer/model.hpp"
#include "scenes/horror_scene/entities/ground.hpp"
#include <glad/glad.h>

namespace Lab
{

    CHorrorScene::CHorrorScene()
        : m_Window(CWindow::GetInstance()),
          m_Skybox(CSkybox::GetInstance()),
          m_Camera(),
          m_Shader(CShader({LAB_BASE_SHADERS_PATH + "gl_basic.vert", LAB_BASE_SHADERS_PATH + "gl_basic.frag"})),
          m_OpaqueSceneEntities({std::make_shared<CGround>(CModel(LAB_BASE_MODELS_PATH + "ground/ground.fbx"))}),
          m_TransparentSceneEntities({std::make_shared<CSceneEntity>(CModel(LAB_BASE_MODELS_PATH + "office_window/office_window.fbx"))})
    {
        m_Skybox.CreateCubemap({LAB_BASE_MODELS_PATH + "skybox_horror_scene/textures/right.png",
                                LAB_BASE_MODELS_PATH + "skybox_horror_scene/textures/left.png",
                                LAB_BASE_MODELS_PATH + "skybox_horror_scene/textures/top.png",
                                LAB_BASE_MODELS_PATH + "skybox_horror_scene/textures/bottom.png",
                                LAB_BASE_MODELS_PATH + "skybox_horror_scene/textures/front.png",
                                LAB_BASE_MODELS_PATH + "skybox_horror_scene/textures/back.png"});

        m_Camera.SetLastPosX(static_cast<float>(m_Window.GetWidth()) / 2.0f);
        m_Camera.SetLastPosY(static_cast<float>(m_Window.GetHeight()) / 2.0f);
    }

    void CHorrorScene::OnUpdate(float t_DeltaTime)
    {
        // Update camera movement
        m_Camera.CameraKeyboardInput(m_Window.GetWindowPointer(), t_DeltaTime);
        m_Camera.CameraMouseMovementInput(m_Window.GetWindowPointer());

        // Process skybox
        m_Skybox.m_Shader.Bind();
        m_Skybox.BindCubemap();

        const glm::mat4 viewMatrix = m_Camera.CalculateViewMatrix();
        const glm::mat4 projectionMatrix = m_Camera.CalculatePerspectiveProjectionMatrix(m_Window);

        m_Skybox.m_Shader.SetUniformMatrix4fv("u_ViewMatrix", glm::mat4(glm::mat3(viewMatrix)));
        m_Skybox.m_Shader.SetUniformMatrix4fv("u_ProjectionMatrix", projectionMatrix);

        glDepthMask(GL_FALSE);
        glCullFace(GL_FRONT);
        m_Skybox.Draw(m_Skybox.m_Shader);
        glDepthMask(GL_TRUE);
        glCullFace(GL_BACK);

        // Bind shader for other entities
        m_Shader.Bind();

        // Process opaque scene entities
        for (const std::shared_ptr<CSceneEntity> &sceneEntity : m_OpaqueSceneEntities)
        {
            glm::mat4 modelMatrix(1.0f);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f));

            m_Shader.SetUniformMatrix4fv("u_ModelMatrix", modelMatrix);
            m_Shader.SetUniformMatrix4fv("u_ViewMatrix", viewMatrix);
            m_Shader.SetUniformMatrix4fv("u_ProjectionMatrix", projectionMatrix);

            sceneEntity->Draw(m_Shader);
        }

        // Process transparent scene entities
        for (const std::shared_ptr<CSceneEntity> &sceneEntity : m_TransparentSceneEntities)
        {
            glm::mat4 modelMatrix(1.0f);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.2f, 0.0f));

            m_Shader.SetUniformMatrix4fv("u_ModelMatrix", modelMatrix);
            m_Shader.SetUniformMatrix4fv("u_ViewMatrix", viewMatrix);
            m_Shader.SetUniformMatrix4fv("u_ProjectionMatrix", projectionMatrix);

            sceneEntity->Draw(m_Shader);
        }
    }

} // namespace Lab
