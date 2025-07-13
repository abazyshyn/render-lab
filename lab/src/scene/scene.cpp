#include "pch.hpp"

#include "scene.hpp" // target

#include "window/window.hpp"
#include "scene/entities/skybox/skybox.hpp"
#include "scene/entities/sponza/sponza.hpp"
#include "renderer/model.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Lab
{
    CScene &CScene::GetInstance()
    {
        static CScene instance;
        return instance;
    }

    CScene::CScene()
        : m_Window(CWindow::GetInstance()),
          m_Skybox(CSkybox::GetInstance()),
          m_SceneShader(CShader({Utils::LAB_BASE_SHADERS_PATH + "gl_horror_scene.vert", Utils::LAB_BASE_SHADERS_PATH + "gl_horror_scene.frag"})),
          m_BasicShader(CShader({Utils::LAB_BASE_SHADERS_PATH + "gl_horror_scene.vert", Utils::LAB_BASE_SHADERS_PATH + "gl_horror_scene.frag"})),
          // m_DebugNormalShader(CShader({Utils::LAB_BASE_SHADERS_PATH + "gl_debug_normal.vert",
          //                              Utils::LAB_BASE_SHADERS_PATH + "gl_debug_normal.geom",
          //                              Utils::LAB_BASE_SHADERS_PATH + "gl_debug_normal.frag"})),
          //  m_ShaderReflect(CShader({Utils::LAB_BASE_SHADERS_PATH + "gl_reflect.vert", Utils::LAB_BASE_SHADERS_PATH + "gl_reflect.frag"})),
          m_OpaqueSceneEntities({std::make_shared<CSponza>()})
    {
        m_Skybox.CreateCubemap({Utils::LAB_BASE_MODELS_PATH + "skybox/textures/right.png",
                                Utils::LAB_BASE_MODELS_PATH + "skybox/textures/left.png",
                                Utils::LAB_BASE_MODELS_PATH + "skybox/textures/top.png",
                                Utils::LAB_BASE_MODELS_PATH + "skybox/textures/bottom.png",
                                Utils::LAB_BASE_MODELS_PATH + "skybox/textures/front.png",
                                Utils::LAB_BASE_MODELS_PATH + "skybox/textures/back.png"});

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

    void CScene::OnUpdate(float t_DeltaTime)
    {
        // Update camera movement
        m_Camera.CameraKeyboardInput(m_Window.GetWindowPointer(), t_DeltaTime);
        m_Camera.CameraMouseMovementInput(m_Window.GetWindowPointer());

        // Set view matrix to the uniform block
        const glm::mat4 viewMatrix = m_Camera.CalculateViewMatrix();

        m_UBO.Bind();
        m_UBO.SetData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(viewMatrix));
        m_UBO.UnBind();

        // Process opaque scene entities
        m_SceneShader.Bind();

        for (const std::shared_ptr<CSceneEntity> &sceneEntity : m_OpaqueSceneEntities)
        {
            glm::mat4 modelMatrix(1.0f);
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.002f));

            m_SceneShader.SetUniformMatrix4fv("u_ModelMatrix", modelMatrix);

            sceneEntity->Draw(m_SceneShader);
        }

        // Process skybox
        m_Skybox.m_Shader.Bind();
        m_Skybox.BindCubemap();

        glDepthFunc(GL_LEQUAL);
        glCullFace(GL_FRONT);
        m_Skybox.Draw(m_Skybox.m_Shader);
        glDepthFunc(GL_LESS);
        glCullFace(GL_BACK);
    }

} // namespace Lab
