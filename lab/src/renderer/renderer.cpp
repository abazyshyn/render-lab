#include "pch.hpp"

#include "renderer.hpp" // target

#include "scenes/i_scene.hpp"
#include "window/window.hpp"
#include "scenes/horror_scene/horror_scene.hpp"
#include "backend/opengl.hpp"
#include <glad/glad.h>

namespace Lab
{

    CRenderer::CRenderer()
        : m_Window(CWindow::GetInstance()),
          m_FBO(CFramebuffer(static_cast<uint32_t>(m_Window.GetWidth()), static_cast<uint32_t>(m_Window.GetHeight()))),
          rectangle(),
          screenShader(CShader({"../../../../lab/res/shaders/gl_screen.vert", "../../../../lab/res/shaders/gl_screen.frag"})),
          m_Scenes({std::make_shared<CHorrorScene>()})
    {
#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)
        OpenGL::EnableDebugOpenGL();
#endif

        // TODO: make enum with all possible indices for scenes
        // HORROR SCENE SETTINGS:
        glDepthFunc(GL_LESS);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void CRenderer::Render(float t_DeltaTime)
    {
        // TODO: make enum with all possible indices for scenes
        for (const std::shared_ptr<CIScene> &pScene : m_Scenes)
        {
            m_FBO.Bind();
            glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_DEPTH_CLAMP);
            glEnable(GL_BLEND);
            glEnable(GL_CULL_FACE);
            pScene->OnUpdate(t_DeltaTime);

            m_FBO.UnBind();
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_DEPTH_CLAMP);
            glDisable(GL_BLEND);
            glDisable(GL_CULL_FACE);
            glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            screenShader.Bind();
            rectangle.DrawRectangle(m_FBO.GetColorBuffer());
        }
    }

} // namespace Lab
