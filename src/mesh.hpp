#pragma once

#include "shader.hpp"

namespace Lab
{

    /**
     * @brief Supported texture types
     */
    enum TextureType_e
    {
        LAB_TEXTURE_TYPE_DIFFUSE = 0,
        LAB_TEXTURE_TYPE_SPECULAR
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
    };

    /**
     * @brief Implementation of a mesh
     *
     * Controls mesh
     */
    class CMesh
    {
    public:
        explicit CMesh(const std::vector<Vertex_s> &vertices, const std::vector<uint32_t> &indices,
                       const std::vector<Texture_s> &textures, const std::string &name);

        CMesh(const CMesh &source) = delete;
        CMesh &operator=(const CMesh &source) = delete;

        CMesh(CMesh &&source) noexcept;
        CMesh &operator=(CMesh &&source) noexcept;

        ~CMesh();

        /**
         * @brief Draws a mesh
         *
         * @param[in] shader Shader program
         */
        void Draw(CShader &shader) const;

        /**
         * @brief Returns mesh name
         *
         * @return Mesh name
         */
        const std::string &GetName() const { return m_Name; }

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
