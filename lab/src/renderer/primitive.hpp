#if !defined(PRIMITIVE_HPP)
#define PRIMITIVE_HPP

namespace Lab
{

    // TODO: add desctiption, and make it a singleton
    class CPrimitive
    {
    public:
        CPrimitive();

        void Draw();

    private:
        uint32_t m_RectangleVAO;

        unsigned char _pad[4] = {}; // Explicit padding

        std::array<float, 24> m_RectangleVertices;

        void SetupRectangle();

        // TODO: create the enum for drawing primitives, eg: TRIANGLE, RECTANGLE
        void DrawRectangle();
    };

} // namespace Lab

#endif // PRIMITIVE_HPP
