#if !defined(UBO_HPP)
#define UBO_HPP

namespace Lab
{
    // TODO: write documentation
    class CUniformBuffer
    {
    public:
        ~CUniformBuffer();

        // TODO: write documentation
        void SetupUBO(uint32_t ct_UniformBlockSize);

        // TODO: write documentation
        void BindRange(uint32_t ct_Index, uint32_t ct_Offset, uint32_t ct_Size) const;

        // TODO: write documentation
        void Bind() const;

        // TODO: write documentation
        void UnBind() const;

        // TODO: write documentation
        void SetData(uint32_t ct_Offset, uint32_t ct_Size, const void *ct_pData);

    private:
        uint32_t m_UBO;
    };

} // namespace Lab

#endif // UBO_HPP
