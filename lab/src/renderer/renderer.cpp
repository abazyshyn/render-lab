#include "pch.hpp"

#include "renderer.hpp"

#include "window/window.hpp"

namespace Lab
{

    CRenderer::CRenderer()
        : m_Window(CWindow::GetInstance()),
          m_FBO(static_cast<uint32_t>(m_Window.GetWidth()), static_cast<uint32_t>(m_Window.GetHeight()))
    {
    }

    void CRenderer::Render()
    {
    }

} // namespace Lab