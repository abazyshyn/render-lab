#include "pch.hpp"

#include "renderer.hpp"

#include "window/window.hpp"
#include "scenes/horror_scene/horror_scene.hpp"

#include <glad/glad.h>

namespace Lab
{

    CRenderer::CRenderer()
        : m_Window(CWindow::GetInstance()),
          // m_FBO(static_cast<uint32_t>(m_Window.GetWidth()), static_cast<uint32_t>(m_Window.GetHeight())),
          m_Scenes({std::make_shared<CHorrorScene>()})
    {
    }

    void CRenderer::Render(float t_DeltaTime)
    {
        // TODO: make enum with all possible indices for scenes
        for (const std::shared_ptr<CIScene> &pScene : m_Scenes)
        {
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_DEPTH_CLAMP);
            glEnable(GL_BLEND);
            glEnable(GL_CULL_FACE);

            glDepthFunc(GL_LESS);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            pScene->OnUpdate(t_DeltaTime);

            glDisable(GL_DEPTH_TEST);
            glDisable(GL_DEPTH_CLAMP);
            glDisable(GL_BLEND);
            glDisable(GL_CULL_FACE);
        }
    }

} // namespace Lab