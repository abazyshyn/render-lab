#pragma once

#include "singleton.hpp"
#include <GLFW/glfw3.h>

namespace Lab
{

    /**
     * @brief Implementation of the platform specific window
     *
     * Implemented using Mayers' Singleton pattern
     * Neither CopyConstructible/MoveConstructible nor
     * CopyAssignable/MoveAssignable
     */
    class CWindow final : public Utils::CSingleton<CWindow>
    {
    public:
        friend Utils::CSingleton<CWindow>;

        ~CWindow();

        /**
         * @brief Updates window
         */
        void OnUpdate();

        /**
         * @brief Returns window status
         *
         * @return Window status
         */
        bool IsRunning() { return m_WindowData.m_IsRunning; }

        /**
         * @brief Returns pointer to a window
         *
         * @return Pointer to a window
         */
        GLFWwindow *GetWindowPointer() const { return m_WindowData.m_pWindow; }

        /**
         * @brief Returns pair of window width and height
         *
         * @return Pair of window width and height
         */
        std::pair<float, float> GetWindowSizes() const
        {
            return {static_cast<float>(m_WindowData.m_WindowWidth), static_cast<float>(m_WindowData.m_WindowHeight)};
        }

    private:
        struct WindowData_s
        {
            GLFWwindow *m_pWindow = nullptr;         // Window pointer
            std::string m_WindowTitle = "RenderLab"; // Window title
            int32_t m_WindowWidth = 1280;            // Window width
            int32_t m_WindowHeight = 720;            // Window height
            bool m_VSync = true;                     // VSync status
            bool m_IsRunning = true;                 // window status

        private:
            unsigned char _pad[6] = {}; // Explicit padding
        } m_WindowData;

        CWindow();

        void Init();
        void Shutdown();
        void SetWindowInputCallbacks();

        static void WindowCloseCallback(GLFWwindow *pWindow);
        static void KeyCallback(GLFWwindow *pWindow, int key, int scancode, int action, int mods);
        static void FramebufferSizeCallback(GLFWwindow *pWindow, int width, int height);
    };

} // namespace Lab
