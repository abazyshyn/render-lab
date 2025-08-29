#pragma once

namespace Lab
{

    // Forward declaration
    class CWindow;
    class CRenderer;

    /**
     * @brief Implementation of the application(render-lab)
     *
     * Implemented using Mayers' Singleton pattern
     *
     * Neither CopyConstructible/MoveConstructible nor
     * CopyAssignable/MoveAssignable
     *
     * Controls whole application
     */
    class CApplication final : public Utils::CSingleton<CApplication>
    {
    public:
        friend Utils::CSingleton<CApplication>;

        /**
         * @brief Main loop
         */
        void Run();

    private:
        CWindow &m_Window;
        CRenderer &m_Renderer;
        float m_LastFrameTime;
        unsigned char _pad[4] = {}; // Explicit padding

        CApplication();

        float CalculateDeltaTime();
    };

} // namespace Lab

