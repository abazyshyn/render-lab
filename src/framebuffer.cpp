#include "pch.hpp"

#include "framebuffer.hpp"
#include <glad/glad.h>

namespace Lab
{

    CFramebuffer::CFramebuffer(uint32_t attachmentWidth, uint32_t attachmentHeight)
        : m_FBO(0),
          m_ColorBuffer(0)
    {
        SetupFramebuffer(attachmentWidth, attachmentHeight);
    }

    CFramebuffer::~CFramebuffer()
    {
        glDeleteFramebuffers(1, &m_FBO);
    }

    void CFramebuffer::Bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    }

    void CFramebuffer::UnBind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void CFramebuffer::OnUpdate(uint32_t attachmentWidth, uint32_t attachmentHeight)
    {
        Bind();

        // Update a color attachment
        glBindTexture(GL_TEXTURE_2D, m_ColorBuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, attachmentWidth, attachmentHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorBuffer, 0);

        // Create a combined depth and stencil attachments
        uint32_t RBO = 0;
        glGenRenderbuffers(1, &RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH32F_STENCIL8, attachmentWidth, attachmentHeight);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        // Attach combined depth and stencil attachments
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            LAB_ERROR_LOG("Framebuffer is not complete.");
            LAB_ASSERT(0);
        }

        UnBind();
    }

    void CFramebuffer::SetupFramebuffer(uint32_t attachmentWidth, uint32_t attachmentHeight)
    {
        glGenFramebuffers(1, &m_FBO);
        Bind();

        // Create a color attachment
        glGenTextures(1, &m_ColorBuffer);
        glBindTexture(GL_TEXTURE_2D, m_ColorBuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, attachmentWidth, attachmentHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        // Attach color attachment to the framebuffer
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorBuffer, 0);

        // Create a combined depth and stencil attachments
        uint32_t RBO = 0;
        glGenRenderbuffers(1, &RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH32F_STENCIL8, attachmentWidth, attachmentHeight);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        // Attach combined depth and stencil attachments
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            LAB_ERROR_LOG("Framebuffer is not complete.");
            LAB_ASSERT(0);
        }

        UnBind();
    }

} // namespace Lab
