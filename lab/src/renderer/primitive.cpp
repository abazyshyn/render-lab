#include "pch.hpp"

#include "primitive.hpp" // target

#include "backend/opengl.hpp"
#include <glad/glad.h>

namespace Lab
{

    CPrimitive &CPrimitive::GetInstance()
    {
        static CPrimitive instance;
        return instance;
    }

    CPrimitive::~CPrimitive()
    {
        OpenGL::DeleteObjects(1, &m_RectangleVAO, 1, &m_RectangleVBO, 1, &m_RectangleIBO);
    }

    void CPrimitive::DrawRectangle(const uint32_t ct_ColorBuffer) const
    {
        glBindVertexArray(m_RectangleVAO);
        glBindTexture(GL_TEXTURE_2D, ct_ColorBuffer);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }

    CPrimitive::CPrimitive()
        : m_RectangleVertices({-1.0f, 1.0f, 0.0f, 1.0f, // Positions 2, Textures 2
                               -1.0f, -1.0f, 0.0f, 0.0f,
                               1.0f, -1.0f, 1.0f, 0.0f,
                               1.0f, 1.0f, 1.0f, 1.0f}),
          m_RectangleIndices({0, 1, 2, 0, 3, 2}),
          m_RectangleVAO(0),
          m_RectangleVBO(0),
          m_RectangleIBO(0)
    {
        SetupRectangle();
    }

    void CPrimitive::SetupRectangle()
    {
        glGenVertexArrays(1, &m_RectangleVAO);
        glGenBuffers(1, &m_RectangleVBO);
        glGenBuffers(1, &m_RectangleIBO);

        glBindVertexArray(m_RectangleVAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_RectangleVBO);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(m_RectangleVertices.size() * sizeof(float)), m_RectangleVertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RectangleIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(m_RectangleIndices.size() * sizeof(uint32_t)), m_RectangleIndices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void *>(2 * sizeof(float)));

        glBindVertexArray(0);
    }

} // namespace Lab
