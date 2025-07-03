#if !defined(RENDERER_HPP)
#define RENDERER_HPP

#include "buffers/framebuffer.hpp"
#include "primitive.hpp"
#include "shader/shader.hpp"

namespace Lab
{
    // Forward declaration
    class CWindow;
    class CIScene;

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
        CFramebuffer m_FBO;

        unsigned char _pad[4] = {}; // Explicit padding

        CPrimitive rectangle; // TODO: temp
        CShader screenShader; // TODO: temp

        std::vector<std::shared_ptr<CIScene>> m_Scenes;
    };

} // namespace Lab

#endif // RENDERER_HPP
