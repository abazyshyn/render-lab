#include "pch.hpp"

#include "primitive.hpp"

#include <glad/glad.h>

namespace Lab
{
    CPrimitive::CPrimitive()
        : m_RectangleVAO(0),
          m_RectangleVertices({-1.0f, 1.0f, 0.0f, 1.0f, // Positions 2, Textures 2
                               -1.0f, -1.0f, 0.0f, 0.0f,
                               1.0f, -1.0f, 1.0f, 0.0f,

                               -1.0f, 1.0f, 0.0f, 1.0f,
                               1.0f, -1.0f, 1.0f, 0.0f,
                               1.0f, 1.0f, 1.0f, 1.0f})
    {
        SetupRectangle();
    }

    void CPrimitive::Draw()
    {
        glBindVertexArray(m_RectangleVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    void CPrimitive::DrawRectangle()
    {
    }

    void CPrimitive::SetupRectangle()
    {
        uint32_t VBO = 0;
        // uint32_t IBO;

        glGenVertexArrays(1, &m_RectangleVAO);
        glGenBuffers(1, &VBO);
        // glGenBuffers(1, &IBO);

        glBindVertexArray(m_RectangleVAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(m_RectangleVertices.size()), &m_RectangleVertices, GL_STATIC_DRAW);

        // TODO: add IBO
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void *>(2 * sizeof(float)));

        glBindVertexArray(0);
    }

} // namespace Lab
