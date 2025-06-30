#if !defined(RENDERER_HPP)
#define RENDERER_HPP

#include "backend/framebuffer.hpp"

namespace Lab
{
    // Forward declaration
    class CWindow;
    class CSceneEntity;

    /**
     * @brief Implementation of the main renderer
     */
    class CRenderer
    {
    public:
        CRenderer();

        void Render();

    private:
        CWindow &m_Window;
        CFramebuffer m_FBO;

        unsigned char _pad[4] = {};
    };

} // namespace Lab

#endif // RENDERER_HPP