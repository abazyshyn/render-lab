#if !defined(WINDOW_HPP)
#define WINDOW_HPP

#include "backend/glfw.hpp"

namespace Lab
{

    /**
     * @brief Implementation of the platform specific window
     *
     * Implemented using Mayers' Singleton pattern
     * Neither CopyConstructible/MoveConstructible nor
     * CopyAssignable/MoveAssignable
     */
    class CWindow
    {
    public:
        /**
         * @brief Indicates status of the main loop
         */
        bool m_IsRunning;

        /**
         * @brief Returns the only one existing instance of the CWindow class
         *
         * @return Instance
         */
        static CWindow &GetInstance();

        CWindow(const CWindow &ct_Source) = delete;
        CWindow(CWindow &&t_Source) = delete;
        ~CWindow();

        CWindow &operator=(const CWindow &ct_RHV) = delete;
        CWindow &operator=(CWindow &&t_RHV) = delete;

        /**
         * @brief Updates window
         */
        void OnUpdate();

        /**
         * @brief Returns pointer to window
         *
         * @return Pointer to window
         */
        [[nodiscard]] GLFWwindow *GetWindowPointer() const { return m_GlfwData.m_pWindow; }
        /**
         * @brief Returns window width
         *
         * @return Window width
         */
        [[nodiscard]] int32_t GetWidth() const { return m_GlfwData.m_WindowWidth; }
        /**
         * @brief Returns window height
         *
         * @return Window height
         */
        [[nodiscard]] int32_t GetHeight() const { return m_GlfwData.m_WindowHeight; }

    private:
        unsigned char _pad[7] = {}; // Explicit padding

        GlfwData_s m_GlfwData;

        CWindow();

        void Init();
        void Shutdown();
    };

} // namespace Lab

#endif // WINDOW_HPP