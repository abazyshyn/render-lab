#include "pch.hpp"

#include "mesh.hpp"
#include "opengl.hpp"
#include <glad/glad.h>

namespace Lab
{

    CMesh::CMesh(const std::vector<Vertex_s> &vertices, const std::vector<uint32_t> &indices,
                 const std::vector<Texture_s> &textures, const std::string &name)
        : m_Vertices(vertices),
          m_Indices(indices),
          m_Textures(textures),
          m_Name(name),
          m_VAO(0),
          m_VBO(0),
          m_IBO(0)
    {
        SetupMesh();
    }

    CMesh::CMesh(CMesh &&source) noexcept
    {
        m_Vertices = std::move(source.m_Vertices);
        m_Indices = std::move(source.m_Indices);
        m_Textures = std::move(source.m_Textures);
        m_Name = std::move(m_Name);
        m_VAO = source.m_VAO;
        m_VBO = source.m_VBO;
        m_IBO = source.m_IBO;

        m_VAO = m_VBO = m_IBO = 0;

        SetupMesh();
    }

    CMesh &CMesh::operator=(CMesh &&source) noexcept
    {
        if (this != &source)
        {
            OpenGL::DeleteObjects(1, &m_VAO, 1, &m_VBO, 1, &m_IBO);

            m_Vertices = std::move(source.m_Vertices);
            m_Indices = std::move(source.m_Indices);
            m_Textures = std::move(source.m_Textures);
            m_Name = std::move(m_Name);
            m_VAO = source.m_VAO;
            m_VBO = source.m_VBO;
            m_IBO = source.m_IBO;

            m_VAO = m_VBO = m_IBO = 0;
        }

        SetupMesh();

        return *this;
    }

    CMesh::~CMesh()
    {
        OpenGL::DeleteObjects(1, &m_VAO, 1, &m_VBO, 1, &m_IBO);
    }

    void CMesh::Draw(CShader &shader) const
    {
        uint32_t diffuseNumber = 0;
        uint32_t specularNumber = 0;

        for (size_t i = 0; i < m_Textures.size(); ++i)
        {
            glActiveTexture(GL_TEXTURE0 + i);

            switch (m_Textures[i].m_TextureType)
            {
                case LAB_TEXTURE_TYPE_DIFFUSE:
                {
                    diffuseNumber += 1;
                    break;
                }

                case LAB_TEXTURE_TYPE_SPECULAR:
                {
                    specularNumber += 1;
                    break;
                }
            }

            switch (m_Textures[i].m_TextureType)
            {
                case LAB_TEXTURE_TYPE_DIFFUSE:
                {
                    std::string uniformTextureName = "u_Material.m_DiffuseTexture";
                    uniformTextureName += std::to_string(i);

                    glUniform1i(glGetUniformLocation(shader.GetProgramId(), uniformTextureName.c_str()), static_cast<int32_t>(i));
                    glBindTexture(GL_TEXTURE_2D, m_Textures[i].m_TextureId);

                    break;
                }
                case LAB_TEXTURE_TYPE_SPECULAR:
                {
                    std::string uniformTextureName = "u_Material.m_SpecularTexture";
                    uniformTextureName += std::to_string(i);

                    glUniform1i(glGetUniformLocation(shader.GetProgramId(), uniformTextureName.c_str()), static_cast<int32_t>(i));
                    glBindTexture(GL_TEXTURE_2D, m_Textures[i].m_TextureId);

                    break;
                }
            }
        }

        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, static_cast<int32_t>(m_Indices.size()), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
    }

    void CMesh::SetupMesh()
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_IBO);

        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        // m_Vertices.size() * sizeof(Vertex_s) - represent a struct as an array of data
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(m_Vertices.size() * sizeof(Vertex_s)), m_Vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(m_Indices.size() * sizeof(uint32_t)), m_Indices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_s), nullptr);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_s), reinterpret_cast<void *>(offsetof(Vertex_s, m_NormalVector)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex_s), reinterpret_cast<void *>(offsetof(Vertex_s, m_TextureCoordinatesVector)));

        glBindVertexArray(0);
    }

} // namespace Lab
