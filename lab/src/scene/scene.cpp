#include "pch.hpp"

#include "scene.hpp" // target

#include "window/window.hpp"
#include "scene/entities/skybox/skybox.hpp"
#include "scene/entities/sponza/sponza.hpp"
#include "scene/entities/lights/lighting_sphere.hpp"
#include "renderer/model.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Lab
{
    // CScene &CScene::GetInstance()
    //{
    //     static CScene instance;
    //     return instance;
    // }

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

        BasicLighting(viewMatrix);

        // Process skybox
        m_Skybox.m_Shader.Bind();
        m_Skybox.BindCubemap();

        glDepthFunc(GL_LEQUAL);
        glCullFace(GL_FRONT);
        m_Skybox.Draw(m_Skybox.m_Shader);
        glDepthFunc(GL_LESS);
        glCullFace(GL_BACK);
    }

    CScene::CScene()
        : m_Window(CWindow::GetInstance()),
          m_Skybox(CSkybox::GetInstance()),
          m_SceneShader(CShader({Utils::LAB_BASE_SHADERS_PATH + "gl_scene.vert", Utils::LAB_BASE_SHADERS_PATH + "gl_scene.frag"})),
          m_BasicShader(CShader({Utils::LAB_BASE_SHADERS_PATH + "gl_scene.vert", Utils::LAB_BASE_SHADERS_PATH + "gl_basic.frag"})),
          m_BasicLightingShader(CShader({Utils::LAB_BASE_SHADERS_PATH + "gl_basic_lighting.vert", Utils::LAB_BASE_SHADERS_PATH + "gl_basic_lighting.frag"})),
          // m_DebugNormalShader(CShader({Utils::LAB_BASE_SHADERS_PATH + "gl_debug_normal.vert",
          //                              Utils::LAB_BASE_SHADERS_PATH + "gl_debug_normal.geom",
          //                              Utils::LAB_BASE_SHADERS_PATH + "gl_debug_normal.frag"})),
          //  m_ShaderReflect(CShader({Utils::LAB_BASE_SHADERS_PATH + "gl_reflect.vert", Utils::LAB_BASE_SHADERS_PATH + "gl_reflect.frag"})),
          m_CommonOpaqueSceneEntities({std::make_shared<CSponza>()}),
          m_BasicLightingOpaqueSceneEntities({std::make_shared<CLightingSphere>()})
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

        SetupBasicLightingScene();
    }

    void CScene::SetupBasicLightingScene()
    {
        m_BasicLightingShader.Bind();

        // Populate u_DirectionalLight struct
        // TODO: color can be changed in the future
        m_BasicLightingShader.SetUniform3fv("u_DirectionalLight.m_DiffuseColor", glm::vec3(1.0f, 1.0f, 1.0f));
        // m_BasicLightingShader.SetUniform3fv("u_DirectionalLight.m_SpecularColor", glm::vec3(1.0f, 1.0f, 1.0f));
    }

    void CScene::BasicLighting(const glm::mat4 &ct_ViewMatrix)
    {
        m_BasicShader.Bind();
        for (const std::shared_ptr<CSceneEntity> &sceneEntity : m_BasicLightingOpaqueSceneEntities)
        {

            glm::mat4 modelMatrix(1.0f);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(1.0f, 0.3f, 0.0f));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.05f));

            m_BasicShader.SetUniformMatrix4fv("u_ModelMatrix", modelMatrix);

            sceneEntity->Draw(m_BasicShader);
        }

        m_BasicLightingShader.Bind();

        m_BasicLightingShader.SetUniform3fv("u_DirectionalLight.m_Position", glm::vec3(ct_ViewMatrix * glm::vec4(1.0f, 0.3f, 0.0f, 1.0f)));

        for (const std::shared_ptr<CSceneEntity> &sceneEntity : m_CommonOpaqueSceneEntities)
        {
            glm::mat4 modelMatrix(1.0f);
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.002f));

            glm::mat3 normalMatrix = static_cast<glm::mat3>(glm::transpose(glm::inverse(ct_ViewMatrix * modelMatrix)));

            m_BasicLightingShader.SetUniformMatrix3fv("u_NormalMatrix", normalMatrix);
            m_BasicLightingShader.SetUniformMatrix4fv("u_ModelMatrix", modelMatrix);

            sceneEntity->Draw(m_BasicLightingShader);
        }
    }

} // namespace Lab
