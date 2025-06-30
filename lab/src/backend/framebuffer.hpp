#if !defined(FRAMEBUFFER_HPP)
#define FRAMEBUFFER_HPP

namespace Lab
{

    /**
     * @brief Implementation of a framebuffer object(FBO)
     */
    class CFramebuffer
    {
    public:
        CFramebuffer(uint32_t ct_AttachmentWidth, uint32_t ct_AttachmentHeight);
        ~CFramebuffer();

        /**
         * @brief Binds a framebuffer to a framebuffer target
         */
        void Bind() const;

        /**
         * @brief Unbinds a framebuffer from a framebuffer target
         */
        void UnBind() const;

    private:
        uint32_t m_FBO;

        void SetupFramebuffer(uint32_t ct_AttachmentWidth, uint32_t ct_AttachmentHeight);
    };

} // namespace Lab

#endif // FRAMEBUFFER_HPP