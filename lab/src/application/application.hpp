#if !defined(APPLICATION_HPP)
#define APPLICATION_HPP

namespace Lab
{
    // Forward declaration
    class CWindow;
    class CRenderer;

    /**
     * @brief Implementation of the application(render-lab)
     *
     * Implemented using Mayers' Singleton pattern
     * Neither CopyConstructible/MoveConstructible nor
     * CopyAssignable/MoveAssignable
     *
     * Controls whole application
     */
    class CApplication
    {
    public:
        /**
         * @brief Returns the only one existing instance of the CApplication class
         *
         * @return Instance
         */
        static CApplication &GetInstance();

        CApplication(const CApplication &ct_Source) = delete;
        CApplication(CApplication &&t_Source) = delete;

        CApplication &operator=(const CApplication &ct_RHV) = delete;
        CApplication &operator=(CApplication &&t_RHV) = delete;

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

#endif // APPLICATION_HPP
