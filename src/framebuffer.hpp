#pragma once

namespace Lab
{

    class CFramebuffer
    {
    public:
        CFramebuffer(uint32_t attachmentWidth, uint32_t attachmentHeight);
        ~CFramebuffer();

        void Bind() const;

        void UnBind() const;

        void OnUpdate(uint32_t attachmentWidth, uint32_t attachmentHeight);

        uint32_t GetColorBuffer() const { return m_ColorBuffer; }

    private:
        uint32_t m_FBO;
        uint32_t m_ColorBuffer;

        void SetupFramebuffer(uint32_t attachmentWidth, uint32_t attachmentHeight);
    };

} // namespace Lab
