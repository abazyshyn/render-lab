#include "pch.hpp"

#include "window.hpp"

namespace Lab
{

    CWindow &CWindow::GetInstance()
    {
        static CWindow s_Instance;
        return s_Instance;
    }

    void CWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_GlfwData.m_pWindow);

        if (!m_GlfwData.m_IsRunning)
        {
            this->m_IsRunning = false;
        }
    }

    CWindow::CWindow()
        : m_IsRunning(true)
    {
        Init();
    }

    CWindow::~CWindow()
    {
        Shutdown();
    }

    void CWindow::Init()
    {
        InitGlfw(m_GlfwData);
        ToggleVerticalSynchronization(m_GlfwData, true);
    }

    void CWindow::Shutdown()
    {
        ShutdownGlfw(m_GlfwData);
    }

} // namespace Lab