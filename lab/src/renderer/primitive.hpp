#if !defined(PRIMITIVE_HPP)
#define PRIMITIVE_HPP

namespace Lab
{

    /**
     * @brief Implementation of the class for drawing a primitives
     *
     * Implemented using Mayers' Singleton pattern
     *
     * Neither CopyConstructible/MoveConstructible nor
     * CopyAssignable/MoveAssignable
     */
    class CPrimitive final : public Utils::CSingleton<CPrimitive>
    {
    public:
        friend class Utils::CSingleton<CPrimitive>;

        ~CPrimitive();

        /**
         * @brief Draws a rectangle
         *
         * param[in] ct_ColorBuffer
         */
        void DrawRectangle(uint32_t ct_ColorBuffer) const;

    private:
        std::array<float, 16> m_RectangleVertices;
        std::array<uint32_t, 6> m_RectangleIndices;

        uint32_t m_RectangleVAO;
        uint32_t m_RectangleVBO;
        uint32_t m_RectangleIBO;

        unsigned char _pad[4] = {}; // Explicit padding

        CPrimitive();

        void SetupRectangle();
    };

} // namespace Lab

#endif // PRIMITIVE_HPP
