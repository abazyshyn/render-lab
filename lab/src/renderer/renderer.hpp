#if !defined(RENDERER_HPP)
#define RENDERER_HPP

// #include "backend/framebuffer.hpp"
#include "scenes/i_scene.hpp"

namespace Lab
{
    // Forward declaration
    class CWindow;
    class CSceneEntity;

    /**
     * @brief Implementation of the main renderer
     */
    class CRenderer // TODO : make singleton
    {
    public:
        CRenderer();

        void Render(float t_DeltaTime);

    private:
        CWindow &m_Window;
        // CFramebuffer m_FBO;
        //
        // unsigned char _pad[4] = {};

        std::vector<std::shared_ptr<CIScene>> m_Scenes;
    };

} // namespace Lab

#endif // RENDERER_HPP