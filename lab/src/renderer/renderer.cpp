#include "pch.hpp"

#include "renderer.hpp" // target

#include "window/window.hpp"
#include "scene/scene.hpp"
#include "primitive.hpp"
#include "backend/opengl.hpp"
#include <glad/glad.h>

namespace Lab
{
    CRenderer &CRenderer::GetInstance()
    {
        static CRenderer instance;
        return instance;
    }

    void CRenderer::Render(float t_DeltaTime)
    {
        // m_FBO.Bind();
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_DEPTH_CLAMP);
        glEnable(GL_BLEND);
        glEnable(GL_CULL_FACE);
        m_Scene.OnUpdate(t_DeltaTime);

        // m_FBO.UnBind();
        // glDisable(GL_DEPTH_TEST);
        // glDisable(GL_DEPTH_CLAMP);
        // glDisable(GL_BLEND);
        // glDisable(GL_CULL_FACE);
        // glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);

        // m_ScreenShader.Bind();
        // m_Primitive.DrawRectangle(m_FBO.GetColorBuffer());
    }

    CRenderer::CRenderer()
        : m_Window(CWindow::GetInstance()),
          m_Scene(CScene::GetInstance()),
          m_Primitive(CPrimitive::GetInstance()),
          m_FBO(CFramebuffer(static_cast<uint32_t>(m_Window.GetWidth()), static_cast<uint32_t>(m_Window.GetHeight()))),
          m_ScreenShader(CShader({Utils::LAB_BASE_SHADERS_PATH + "gl_screen.vert", Utils::LAB_BASE_SHADERS_PATH + "gl_screen.frag"}))
    {
#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)
        OpenGL::EnableDebug();
#endif // defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)

        // TODO: make enum with all possible indices for scenes
        // HORROR SCENE SETTINGS:
        glDepthFunc(GL_LESS);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // Common
        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS); // For an old hardware
    }

} // namespace Lab
