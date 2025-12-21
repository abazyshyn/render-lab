#include "pch.hpp"
#include "resident_evil.hpp"
#include "utils.hpp"
#include <glad/glad.h>

namespace Lab
{

    void CResidentEvilScene::SetupScene()
    {
    }

    void CResidentEvilScene::OnUpdate(float t_DeltaTime, CCamera &t_Camera, CWindow &t_Window)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(0.2f, 1.0f, 0.2f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_DEPTH_CLAMP);
        glDepthFunc(GL_LESS);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        m_DiningRoomShader.Bind();

        t_Camera.CameraKeyboardInput(t_Window.GetWindowPointer(), t_DeltaTime);
        t_Camera.CameraMouseMovementInput(t_Window.GetWindowPointer());

        glm::mat4 modelMatrix(1.0f);
        glm::mat4 viewMatrix = t_Camera.CalculateViewMatrix();
        // glm::mat3 normalMatrix = glm::transpose(glm::inverse(modelMatrix));
        glm::mat4 projectionMatrix = t_Camera.CalculatePerspectiveProjectionMatrix(t_Window);

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
