#if !defined(PRIMITIVE_HPP)
#define PRIMITIVE_HPP

namespace Lab
{

    // TODO: add desctiption, and make it a singleton
    class CPrimitive
    {
    public:
        CPrimitive();
        ~CPrimitive();

        void DrawRectangle(uint32_t ct_ColorBuffer) const;

    private:
        std::array<float, 16> m_RectangleVertices;
        std::array<uint32_t, 6> m_RectangleIndices;

        uint32_t m_RectangleVAO;
        uint32_t m_RectangleVBO;
        uint32_t m_RectangleIBO;

        unsigned char _pad[4] = {}; // Explicit padding

        void SetupRectangle();
    };

} // namespace Lab

#endif // PRIMITIVE_HPP
