#include "pch.hpp"

#include "application.hpp"
#include "window/window.hpp"

namespace Lab
{

    CApplication &CApplication::GetInstance()
    {
        static CApplication s_Instance;
        return s_Instance;
    }

    void CApplication::Run()
    {
        while (m_Window.m_IsRunning)
        {
            float deltaTime = CalculateDeltaTime();

            m_Window.OnUpdate();
            m_Renderer.Render(deltaTime);
        }
    }

    CApplication::CApplication()
        : m_Window(CWindow::GetInstance()),
          m_Renderer(),
          m_LastFrameTime(0.0f)
    {
    }

    float CApplication::CalculateDeltaTime()
    {
        float deltaTime = 0.0f;

        const float curFrameTime = static_cast<float>(glfwGetTime());
        deltaTime = curFrameTime - m_LastFrameTime;
        m_LastFrameTime = curFrameTime;

        return deltaTime;
    }

} // namespace Lab