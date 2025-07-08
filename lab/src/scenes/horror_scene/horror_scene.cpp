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
          m_UBO(),
          m_Shader(CShader({Utils::LAB_BASE_SHADERS_PATH + "gl_basic.vert", Utils::LAB_BASE_SHADERS_PATH + "gl_basic.frag"})),
          m_ShaderReflect(CShader({Utils::LAB_BASE_SHADERS_PATH + "gl_reflect.vert", Utils::LAB_BASE_SHADERS_PATH + "gl_reflect.frag"})),
          m_OpaqueSceneEntities({std::make_shared<CGround>(CModel(Utils::LAB_BASE_MODELS_PATH + "ground/ground.fbx"))}),
          m_ReflectiveObjects({std::make_shared<CSceneEntity>(CModel(Utils::LAB_BASE_MODELS_PATH + "skybox_horror_scene/skybox.fbx"))}),
          m_TransparentSceneEntities({std::make_shared<CSceneEntity>(CModel(Utils::LAB_BASE_MODELS_PATH + "office_window/office_window.fbx"))})
    {
        m_Skybox.CreateCubemap({Utils::LAB_BASE_MODELS_PATH + "skybox_horror_scene/textures/right.png",
                                Utils::LAB_BASE_MODELS_PATH + "skybox_horror_scene/textures/left.png",
                                Utils::LAB_BASE_MODELS_PATH + "skybox_horror_scene/textures/top.png",
                                Utils::LAB_BASE_MODELS_PATH + "skybox_horror_scene/textures/bottom.png",
                                Utils::LAB_BASE_MODELS_PATH + "skybox_horror_scene/textures/front.png",
                                Utils::LAB_BASE_MODELS_PATH + "skybox_horror_scene/textures/back.png"});

        m_Camera.SetLastPosX(static_cast<float>(m_Window.GetWidth()) / 2.0f);
        m_Camera.SetLastPosY(static_cast<float>(m_Window.GetHeight()) / 2.0f);

        m_UBO.SetupUBO(2 * sizeof(glm::mat4));
        m_UBO.BindRange(0, 0, 2 * sizeof(glm::mat4));

        // Set projection matrix to the uniform block
        const glm::mat4 projectionMatrix = m_Camera.CalculatePerspectiveProjectionMatrix(m_Window);

        m_UBO.Bind();
        m_UBO.SetData(0, sizeof(glm::mat4), glm::value_ptr(projectionMatrix));
        m_UBO.UnBind();
    }

    void CHorrorScene::OnUpdate(float t_DeltaTime)
    {
        // Update camera movement
        m_Camera.CameraKeyboardInput(m_Window.GetWindowPointer(), t_DeltaTime);
        m_Camera.CameraMouseMovementInput(m_Window.GetWindowPointer());

        // Set view matrix to the uniform block
        const glm::mat4 viewMatrix = m_Camera.CalculateViewMatrix();

        m_UBO.Bind();
        m_UBO.SetData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(viewMatrix));
        m_UBO.UnBind();

        //// Process opaque scene entities
        // m_Shader.Bind();

        // for (const std::shared_ptr<CSceneEntity> &sceneEntity : m_OpaqueSceneEntities)
        //{
        //     glm::mat4 modelMatrix(1.0f);
        //     modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f));

        //    m_Shader.SetUniformMatrix4fv("u_ModelMatrix", modelMatrix);

        //    sceneEntity->Draw(m_Shader);
        //}

        // Process skybox
        m_Skybox.m_Shader.Bind();
        m_Skybox.BindCubemap();

        glDepthFunc(GL_LEQUAL);
        glCullFace(GL_FRONT);
        m_Skybox.Draw(m_Skybox.m_Shader);
        glDepthFunc(GL_LESS);
        glCullFace(GL_BACK);

        // Process reflective objects
        m_ShaderReflect.Bind();

        for (const std::shared_ptr<CSceneEntity> &sceneEntity : m_ReflectiveObjects)
        {
            glm::mat4 modelMatrix(1.0f);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(1.0f, 0.2f, 0.0f));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2));

            m_ShaderReflect.SetUniformMatrix4fv("u_ModelMatrix", modelMatrix);
            m_ShaderReflect.SetUniform3fv("u_CameraPosition", m_Camera.GetCameraPos());

            sceneEntity->Draw(m_ShaderReflect);
        }

        // Process transparent scene entities
        m_Shader.Bind();

        for (const std::shared_ptr<CSceneEntity> &sceneEntity : m_TransparentSceneEntities)
        {
            glm::mat4 modelMatrix(1.0f);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.2f, 0.0f));

            m_Shader.SetUniformMatrix4fv("u_ModelMatrix", modelMatrix);

            sceneEntity->Draw(m_Shader);
        }
    }

} // namespace Lab
