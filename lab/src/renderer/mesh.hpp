#if !defined(MESH_HPP)
#define MESH_HPP

namespace Lab
{
    // Forward declaration
    class CShader;

    /**
     * @brief Supported texture types
     */
    enum TextureType_e
    {
        LAB_TEXTURE_TYPE_DIFFUSE = 0,
        LAB_TEXTURE_TYPE_SPECULAR,
    };

    /**
     * @brief Implementation of a vertex data
     */
    struct Vertex_s
    {
        glm::vec3 m_PositionVector;
        glm::vec3 m_NormalVector;
        glm::vec2 m_TextureCoordinatesVector;
    };

    /**
     * @brief Implementation of a texture
     */
    struct Texture_s
    {
        std::string m_TexturePath;
        TextureType_e m_TextureType;
        uint32_t m_TextureId;
        float m_Shininess = 0.0f;

    private:
        unsigned char _pad[4] = {}; // Explicit padding
    };

    /**
     * @brief Implementation of a mesh
     *
     * Controls mesh
     */
    class CMesh
    {
    public:
        explicit CMesh(const std::vector<Vertex_s> &ct_Vertices, const std::vector<uint32_t> &ct_Indices,
                       const std::vector<Texture_s> &ct_Textures, const std::string &ct_Name);
        ~CMesh();

        /**
         * @brief Draws a mesh
         *
         * @param[in] ct_Shader Shader program
         */
        void Draw(CShader &ct_Shader) const;

        /**
         * @brief Returns mesh name
         *
         * @return Mesh name
         */
        [[nodiscard]] const std::string &GetName() const { return m_Name; }

    private:
        std::vector<Vertex_s> m_Vertices;
        std::vector<uint32_t> m_Indices;
        std::vector<Texture_s> m_Textures;
        std::string m_Name;
        uint32_t m_VAO;
        uint32_t m_VBO;
        uint32_t m_IBO;
        unsigned char _pad[4] = {}; // Explicit padding

        void SetupMesh();
    };

} // namespace Lab

#endif // MESH_HPP
