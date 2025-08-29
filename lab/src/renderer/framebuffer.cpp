#include "pch.hpp"

#include "framebuffer.hpp" // target

#include <glad/glad.h>

namespace Lab
{

    CFramebuffer::CFramebuffer(const uint32_t ct_AttachmentWidth, const uint32_t ct_AttachmentHeight)
        : m_FBO(0),
          m_ColorBuffer(0)
    {
        SetupFBO(ct_AttachmentWidth, ct_AttachmentHeight);
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

    void CFramebuffer::SetupFBO(const uint32_t ct_AttachmentWidth, const uint32_t ct_AttachmentHeight)
    {
        glGenFramebuffers(1, &m_FBO);
        this->Bind();

        // Create a color attachment
        glGenTextures(1, &m_ColorBuffer);
        glBindTexture(GL_TEXTURE_2D, m_ColorBuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ct_AttachmentWidth, ct_AttachmentHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        // Attach color attachment to the framebuffer
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorBuffer, 0);

        // Create a combined depth and stencil attachments
        uint32_t RBO = 0;
        glGenRenderbuffers(1, &RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, ct_AttachmentWidth, ct_AttachmentHeight);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        // Attach combined depth and stencil attachments
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_ERROR, "Framebuffer is not complete.");
            LAB_ASSERT(0);
        }

        this->UnBind();
    }

} // namespace Lab
