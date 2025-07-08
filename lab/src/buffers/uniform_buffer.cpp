#include "pch.hpp"

#include "uniform_buffer.hpp" // target

#include <glad/glad.h>

namespace Lab
{

    CUniformBuffer::~CUniformBuffer()
    {
    }

    void CUniformBuffer::SetupUBO(const uint32_t ct_UniformBlockSize)
    {
        glGenBuffers(1, &m_UBO);
        glBindBuffer(GL_UNIFORM_BUFFER, m_UBO);
        glBufferData(GL_UNIFORM_BUFFER, static_cast<GLsizeiptr>(ct_UniformBlockSize), nullptr, GL_STATIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void CUniformBuffer::BindRange(const uint32_t ct_Index, const uint32_t ct_Offset, const uint32_t ct_Size) const
    {
        glBindBufferRange(GL_UNIFORM_BUFFER, ct_Index, m_UBO, static_cast<GLintptr>(ct_Offset), static_cast<GLsizeiptr>(ct_Size));
    }

    void CUniformBuffer::Bind() const
    {
        glBindBuffer(GL_UNIFORM_BUFFER, m_UBO);
    }

    void CUniformBuffer::UnBind() const
    {
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void CUniformBuffer::SetData(const uint32_t ct_Offset, const uint32_t ct_Size, const void *ct_pData)
    {
        glBufferSubData(GL_UNIFORM_BUFFER, static_cast<GLintptr>(ct_Offset), static_cast<GLsizeiptr>(ct_Size), ct_pData);
    }

} // namespace Lab
