#pragma once

namespace Lab
{

    /**
     * @brief Implementation of a framebuffer object(FBO)
     */
    class CFramebuffer
    {
    public:
        explicit CFramebuffer(uint32_t ct_AttachmentWidth, uint32_t ct_AttachmentHeight);
        ~CFramebuffer();

        /**
         * @brief Binds a framebuffer to a framebuffer target
         */
        void Bind() const;

        /**
         * @brief Unbinds a framebuffer from a framebuffer target
         */
        void UnBind() const;

        /**
         * @brief Returns color buffer
         *
         * @return Color buffer
         */
        [[nodiscard]] uint32_t GetColorBuffer() const { return m_ColorBuffer; }

    private:
        uint32_t m_FBO;
        uint32_t m_ColorBuffer;

        void SetupFBO(uint32_t ct_AttachmentWidth, uint32_t ct_AttachmentHeight);
    };

} // namespace Lab
