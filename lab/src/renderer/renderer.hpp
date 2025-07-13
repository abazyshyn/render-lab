#if !defined(RENDERER_HPP)
#define RENDERER_HPP

#include "buffers/framebuffer.hpp"
#include "shader/shader.hpp"

namespace Lab
{
    // Forward declaration
    class CWindow;
    class CScene;
    class CPrimitive;

    /**
     * @brief Implementation of the main renderer
     *
     * Implemented using Mayers' Singleton pattern
     * Neither CopyConstructible/MoveConstructible nor
     * CopyAssignable/MoveAssignable
     */
    class CRenderer
    {
    public:
        /**
         * @brief Returns the only one existing instance of the CRenderer class
         *
         * @return Instance
         */
        static CRenderer &GetInstance();

        CRenderer(const CRenderer &ct_Source) = delete;
        CRenderer(CRenderer &&t_Source) = delete;

        CRenderer &operator=(const CRenderer &ct_RHV) = delete;
        CRenderer &operator=(CRenderer &&t_RHV) = delete;

        /**
         * @brief Main renderer, renders and manages all scenes
         *
         * @param[in] t_DeltaTime Delta time
         */
        void Render(float t_DeltaTime);

    private:
        CWindow &m_Window;
        CScene &m_Scene;
        CPrimitive &m_Primitive; // Screen
        CFramebuffer m_FBO;
        CShader m_ScreenShader; // TODO: temp

        CRenderer();
    };

} // namespace Lab

#endif // RENDERER_HPP
