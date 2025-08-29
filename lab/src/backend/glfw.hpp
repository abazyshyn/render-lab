#pragma once

#include <GLFW/glfw3.h>

namespace GLFW
{

    /**
     *  @brief Contains data for any kind of interactions with GLFW library
     */
    struct GlfwData_s
    {
        GLFWwindow *m_pWindow = nullptr;         // Window pointer
        std::string m_WindowTitle = "RenderLab"; // Window title
        int32_t m_WindowWidth = 1280;            // Window width
        int32_t m_WindowHeight = 720;            // Window height
        bool m_VSync = true;                     // VSync status
        bool m_IsRunning = true;                 // window status

    private:
        unsigned char _pad[6] = {}; // Explicit padding
    };

    /**
     * @brief Initializes GLFW window
     *
     * @param[in] t_GlfwData Data required to initialize GLFW window
     */
    void InitGlfw(GlfwData_s &t_GlfwData);

    /**
     * @brief Shutdowns GLFW window
     *
     * @param[in] ct_GlfwData Data required to shut down GLFW window
     */
    void ShutdownGlfw(const GlfwData_s &ct_GlfwData);

    /**
     * @brief Enables or disables VSync
     *
     * @param[in] t_GlfwData
     * @param[in] ct_IsVSync VSync state
     */
    void ToggleVerticalSynchronization(GlfwData_s &t_GlfwData, bool ct_IsVSync);

    /**
     * @brief Sets window input callbacks
     *
     * @param[in] ct_GlfwData Data required set window input callbacks
     */
    void SetWindowInputCallbacks(const GlfwData_s &ct_GlfwData);

    /**
     * @brief The function for window close callbacks.
     *
     * @param[in] t_pWindow The window that the user attempted to close.
     */
    void WindowCloseCallback(GLFWwindow *t_pWindow);

    /**
     * @brief The function for keyboard key callbacks.
     *
     * @param[in] t_pWindow The window that received the event.
     * @param[in] t_Key The keyboard key that was pressed or released.
     * @param[in] t_Scancode The platform-specific scancode of the key.
     * @param[in] t_Action `GLFW_PRESS`, `GLFW_RELEASE` or `GLFW_REPEAT`.  Future
     * releases may add more actions.
     * @param[in] t_Mods Bit field describing which modifier keys were held down.
     */
    void KeyCallback(GLFWwindow *t_pWindow, int t_Key, int t_Scancode, int t_Action, int t_Mods);

    /**
     * @brief The function for framebuffer size callbacks.
     *
     * @param[in] t_pWindow The window whose framebuffer was resized.
     * @param[in] t_Width The new width, in pixels, of the framebuffer.
     * @param[in] t_Height The new height, in pixels, of the framebuffer.
     */
    void FramebufferSizeCallback(GLFWwindow *t_pWindow, int t_Width, int t_Height);

} // namespace GLFW
