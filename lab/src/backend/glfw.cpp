#include "pch.hpp"

#include "glfw.hpp"
#include <glad/glad.h>

namespace Lab
{

    void InitGlfw(GlfwData_s &t_GlfwData)
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

        t_GlfwData.m_pWindow = glfwCreateWindow(
            t_GlfwData.m_WindowWidth, t_GlfwData.m_WindowHeight,
            t_GlfwData.m_WindowTitle.c_str(), nullptr, nullptr);

        // Check window pointer
        LAB_ASSERT(t_GlfwData.m_pWindow);

        glfwMakeContextCurrent(t_GlfwData.m_pWindow);
        glfwSetWindowUserPointer(t_GlfwData.m_pWindow, &t_GlfwData);
        SetWindowInputCallbacks(t_GlfwData);

        initializationStatus = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

        // Check initialization
        LAB_ASSERT(initializationStatus);

        glViewport(0, 0, t_GlfwData.m_WindowWidth, t_GlfwData.m_WindowHeight);

        LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_WARNING, "Window created.");
    }

    void ShutdownGlfw(const GlfwData_s &ct_GlfwData)
    {
        LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_WARNING, "Window destroyed.");

        glfwDestroyWindow(ct_GlfwData.m_pWindow);
        glfwTerminate();
    }

    void ToggleVerticalSynchronization(GlfwData_s &t_GlfwData, const bool ct_IsVSync)
    {
        t_GlfwData.m_VSync = ct_IsVSync;

        glfwSwapInterval(ct_IsVSync ? 1 : 0);
    }

    void SetWindowInputCallbacks(const GlfwData_s &ct_GlfwData)
    {
        glfwSetWindowCloseCallback(ct_GlfwData.m_pWindow, WindowCloseCallback);
        glfwSetKeyCallback(ct_GlfwData.m_pWindow, KeyCallback);
        glfwSetFramebufferSizeCallback(ct_GlfwData.m_pWindow, FramebufferSizeCallback);
    }

    void WindowCloseCallback(GLFWwindow *t_pWindow)
    {
        GlfwData_s &glfwData = *static_cast<GlfwData_s *>(glfwGetWindowUserPointer(t_pWindow));

        glfwData.m_IsRunning = false;
    }

    void KeyCallback(GLFWwindow *t_pWindow, int t_Key, int t_Scancode, int t_Action,
                     int t_Mods)
    {
        GlfwData_s &glfwData = *static_cast<GlfwData_s *>(glfwGetWindowUserPointer(t_pWindow));

        // Close window
        if ((glfwGetKey(t_pWindow, GLFW_KEY_LEFT_SHIFT) ||
             glfwGetKey(t_pWindow, GLFW_KEY_RIGHT_SHIFT)) &&
            glfwGetKey(t_pWindow, GLFW_KEY_ESCAPE))
        {
            LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_WARNING,
                    "SHIFT + ESCAPE keys pressed.");

            glfwData.m_IsRunning = false;
            return;
        }

        if ((glfwGetKey(t_pWindow, GLFW_KEY_LEFT_CONTROL) ||
             glfwGetKey(t_pWindow, GLFW_KEY_RIGHT_CONTROL)) &&
            (glfwGetKey(t_pWindow, GLFW_KEY_LEFT_SHIFT) ||
             glfwGetKey(t_pWindow, GLFW_KEY_RIGHT_SHIFT)) &&
            glfwGetKey(t_pWindow, GLFW_KEY_C))
        {
            LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_WARNING,
                    "CONTROL + SHIFT + C keys pressed.");

            glfwSetInputMode(t_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            return;
        }

        if ((glfwGetKey(t_pWindow, GLFW_KEY_LEFT_CONTROL) ||
             glfwGetKey(t_pWindow, GLFW_KEY_RIGHT_CONTROL)) &&
            (glfwGetKey(t_pWindow, GLFW_KEY_LEFT_SHIFT) ||
             glfwGetKey(t_pWindow, GLFW_KEY_RIGHT_SHIFT)) &&
            glfwGetKey(t_pWindow, GLFW_KEY_X))
        {
            LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_WARNING,
                    "CONTROL + SHIFT + C keys pressed.");

            glfwSetInputMode(t_pWindow, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
            return;
        }
    }

    void FramebufferSizeCallback(GLFWwindow *t_pWindow, int t_Width, int t_Height)
    {
        GlfwData_s &glfwData = *static_cast<GlfwData_s *>(glfwGetWindowUserPointer(t_pWindow));

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

} // namespace Lab