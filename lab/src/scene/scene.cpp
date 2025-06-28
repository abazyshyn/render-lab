#include "pch.hpp"

#include "scene.hpp"
// #include "car.hpp"
#include "window/window.hpp"
#include "camera/camera.hpp"

// test
#include "glad/glad.h"

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

        shader.Bind();

        m_pCamera->CameraKeyboardInput(m_Window.GetWindowPointer(), t_DeltaTime);
        m_pCamera->CameraMouseMovementInput(m_Window.GetWindowPointer());

        for (const auto &m : tempModels)
        {
            glm::mat4 modelMatrix(1.0f);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f));
            const glm::mat4 viewMatrix = m_pCamera->CalculateViewMatrix();
            const glm::mat4 projectionMatrix = m_pCamera->CalculatePerspectiveProjectionMatrix(m_Window);

            if (m.GetName() == "office_window.fbx")
            {
                std::map<float, glm::vec3>::reverse_iterator it = sortedWindowPositions.rbegin();
                for (it; it != sortedWindowPositions.rend(); ++it)
                {
                    modelMatrix = glm::translate(modelMatrix, it->second);

                    shader.SetUniformMatrix4fv("u_ModelMatrix", modelMatrix);
                    shader.SetUniformMatrix4fv("u_ViewMatrix", viewMatrix);
                    shader.SetUniformMatrix4fv("u_ProjectionMatrix", projectionMatrix);

                    m.Draw(shader);
                }
                continue;
            }

            shader.SetUniformMatrix4fv("u_ModelMatrix", modelMatrix);
            shader.SetUniformMatrix4fv("u_ViewMatrix", viewMatrix);
            shader.SetUniformMatrix4fv("u_ProjectionMatrix", projectionMatrix);

            m.Draw(shader);
        }

        shader.UnBind();
    }

    CScene::CScene()
        : m_pCamera(std::make_unique<CCamera>()),
          m_Window(CWindow::GetInstance())
    //   m_pSceneEntities({std::make_unique<CCar>("res/toyota-ae86/ae86.fbx",
    //                                               std::vector<std::string>{"res/shaders/", "res/shaders/"})})
    {
        glEnable(GL_DEPTH_TEST);  // temporary
        glEnable(GL_DEPTH_CLAMP); // there is no near or far plane clipping
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDepthFunc(GL_LESS);

        m_pCamera->SetLastPosX(static_cast<float>(m_Window.GetWidth()) / 2.0f);
        m_pCamera->SetLastPosY(static_cast<float>(m_Window.GetHeight()) / 2.0f);

        for (const glm::vec3 &pos : windowPositions)
        {
            float distance = glm::length(m_pCamera->GetCameraPos() - pos);
            sortedWindowPositions[distance] = pos;
        }
    }

} // namespace Lab