#pragma once

#include "framebuffer.hpp"
#include "shader.hpp"

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
     *
     * Neither CopyConstructible/MoveConstructible nor
     * CopyAssignable/MoveAssignable
     */
    class CRenderer final : public Utils::CSingleton<CRenderer>
    {
    public:
        friend class Utils::CSingleton<CRenderer>;

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

