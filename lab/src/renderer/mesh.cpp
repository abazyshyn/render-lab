#include "pch.hpp"

#include "shader/shader.hpp"

#include "mesh.hpp" // target

#include "backend/opengl.hpp"
#include <glad/glad.h>

namespace Lab
{

    CMesh::CMesh(const std::vector<Vertex_s> &ct_Vertices, const std::vector<uint32_t> &ct_Indices,
                 const std::vector<Texture_s> &ct_Textures, const std::string &ct_Name)
        : m_Vertices(ct_Vertices),
          m_Indices(ct_Indices),
          m_Textures(ct_Textures),
          m_Name(ct_Name),
          m_VAO(0),
          m_VBO(0),
          m_IBO(0)
    {
        SetupMesh();
    }

    CMesh::~CMesh()
    {
        // LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_WARNING, "CALLED ", this->GetName());
        // LAB_ASSERT(0);
        //  OpenGL::DeleteObjects(1, &m_VAO, 1, &m_VBO, 1, &m_IBO);
    }

    void CMesh::Draw(const CShader &ct_Shader) const
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

            if (m_Textures[i].m_TextureType == LAB_TEXTURE_TYPE_DIFFUSE)
            {
                std::string uniformTextureName = "u_DiffuseTexture";
                uniformTextureName += std::to_string(i);

                glUniform1i(glGetUniformLocation(ct_Shader.GetProgramId(), uniformTextureName.c_str()), static_cast<int32_t>(i));
                glBindTexture(GL_TEXTURE_2D, m_Textures[i].m_TextureId);
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
