#include "pch.hpp"

#include "window.hpp"

#include <glad/glad.h>

namespace Lab
{

    CWindow::~CWindow()
    {
        Shutdown();
    }

    void CWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_WindowData.m_pWindow);

        if (!m_WindowData.m_IsRunning)
        {
            m_WindowData.m_IsRunning = false;
        }
    }

    CWindow::CWindow()
    {
        Init();
    }

    void CWindow::Init()
    {
        int32_t initializationStatus = glfwInit();

        // Check initialization
        LAB_ASSERT(initializationStatus);

        // Window related hints
        glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_FALSE); // TODO: maybe it should be GLFW_TRUE
        // Framebuffer related hints
        glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
        // Context related hints
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);

#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)

        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

#endif

        m_WindowData.m_pWindow = glfwCreateWindow(m_WindowData.m_WindowWidth, m_WindowData.m_WindowHeight,
                                                  m_WindowData.m_WindowTitle.c_str(), nullptr, nullptr);

        // Check window pointer
        LAB_ASSERT(m_WindowData.m_pWindow);

        glfwMakeContextCurrent(m_WindowData.m_pWindow);
        glfwSetWindowUserPointer(m_WindowData.m_pWindow, &m_WindowData);
        SetWindowInputCallbacks();

        initializationStatus = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

        // Check initialization
        LAB_ASSERT(initializationStatus);

        glViewport(0, 0, m_WindowData.m_WindowWidth, m_WindowData.m_WindowHeight);

        LAB_INFO_LOG("GLFW window created.");
    }

    void CWindow::SetWindowInputCallbacks()
    {
        glfwSetWindowCloseCallback(m_WindowData.m_pWindow, WindowCloseCallback);
        glfwSetKeyCallback(m_WindowData.m_pWindow, KeyCallback);
        glfwSetFramebufferSizeCallback(m_WindowData.m_pWindow, FramebufferSizeCallback);
    }

    void CWindow::Shutdown()
    {
        LAB_INFO_LOG("GLFW window destroyed.");
        glfwDestroyWindow(m_WindowData.m_pWindow);
        glfwTerminate();
    }

#pragma region Callbacks

    void CWindow::WindowCloseCallback(GLFWwindow *t_pWindow)
    {
        WindowData_s &glfwData = *static_cast<WindowData_s *>(glfwGetWindowUserPointer(t_pWindow));

        glfwData.m_IsRunning = false;
    }

    void CWindow::KeyCallback(GLFWwindow *t_pWindow, int t_Key, int t_Scancode, int t_Action, int t_Mods)
    {
        WindowData_s &glfwData = *static_cast<WindowData_s *>(glfwGetWindowUserPointer(t_pWindow));

        // Close window
        if ((glfwGetKey(t_pWindow, GLFW_KEY_LEFT_SHIFT) ||
             glfwGetKey(t_pWindow, GLFW_KEY_RIGHT_SHIFT)) &&
            glfwGetKey(t_pWindow, GLFW_KEY_ESCAPE))
        {
            LAB_TRACE_LOG("SHIFT + ESCAPE keys pressed.");
            glfwData.m_IsRunning = false;
            return;
        }

        // Hide cursor
        if ((glfwGetKey(t_pWindow, GLFW_KEY_LEFT_CONTROL) ||
             glfwGetKey(t_pWindow, GLFW_KEY_RIGHT_CONTROL)) &&
            (glfwGetKey(t_pWindow, GLFW_KEY_LEFT_SHIFT) ||
             glfwGetKey(t_pWindow, GLFW_KEY_RIGHT_SHIFT)) &&
            glfwGetKey(t_pWindow, GLFW_KEY_C))
        {
            LAB_TRACE_LOG("CONTROL + SHIFT + C keys pressed.");
            glfwSetInputMode(t_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            return;
        }

        // Show cursor
        if ((glfwGetKey(t_pWindow, GLFW_KEY_LEFT_CONTROL) ||
             glfwGetKey(t_pWindow, GLFW_KEY_RIGHT_CONTROL)) &&
            (glfwGetKey(t_pWindow, GLFW_KEY_LEFT_SHIFT) ||
             glfwGetKey(t_pWindow, GLFW_KEY_RIGHT_SHIFT)) &&
            glfwGetKey(t_pWindow, GLFW_KEY_X))
        {
            LAB_TRACE_LOG("CONTROL + SHIFT + X keys pressed.");
            glfwSetInputMode(t_pWindow, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
            return;
        }

        // Turn on wireframe mode
        if ((glfwGetKey(t_pWindow, GLFW_KEY_LEFT_SHIFT) ||
             glfwGetKey(t_pWindow, GLFW_KEY_RIGHT_SHIFT)) &&
            glfwGetKey(t_pWindow, GLFW_KEY_Q))
        {
            LAB_TRACE_LOG("SHIFT + Q keys pressed.");
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            return;
        }

        // Turn off wireframe mode
        if ((glfwGetKey(t_pWindow, GLFW_KEY_LEFT_CONTROL) ||
             glfwGetKey(t_pWindow, GLFW_KEY_RIGHT_CONTROL)) &&
            glfwGetKey(t_pWindow, GLFW_KEY_Q))
        {
            LAB_TRACE_LOG("CONTROL + Q keys pressed.");
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            return;
        }
    }

    void CWindow::FramebufferSizeCallback(GLFWwindow *t_pWindow, int t_Width, int t_Height)
    {
        WindowData_s &glfwData = *static_cast<WindowData_s *>(glfwGetWindowUserPointer(t_pWindow));

        if (t_Width == 0 && t_Height == 0)
        {
            glfwData.m_WindowWidth = 1;
            glfwData.m_WindowHeight = 1;
        }
        else
        {
            glfwData.m_WindowWidth = t_Width;
            glfwData.m_WindowHeight = t_Height;
        }

        glViewport(0, 0, glfwData.m_WindowWidth, glfwData.m_WindowHeight);
    }

#pragma endregion Callbacks

} // namespace Lab
