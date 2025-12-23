#include "pch.hpp"
#include "resident_evil.hpp"
#include "utils.hpp"
#include <glad/glad.h>

namespace Lab
{

    void CResidentEvilScene::SetupScene()
    {
    }

    void CResidentEvilScene::OnUpdate(float deltaTime, CCamera &camera, CWindow &window)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(0.2f, 1.0f, 0.2f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_DEPTH_CLAMP);
        glDepthFunc(GL_LESS);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

        m_DiningRoomModel.Draw(m_DiningRoomShader);
    }

    CResidentEvilScene::CResidentEvilScene()
        : m_DiningRoomModel(Utils::LAB_BASE_MODELS_PATH + "resident_evil_scene/dining_room/scene.gltf"),
          m_DiningRoomShader({Utils::LAB_BASE_SHADERS_PATH + "gl_dining_room.vert",
                              Utils::LAB_BASE_SHADERS_PATH + "gl_dining_room.frag"})
    {
    }

} // namespace Lab
