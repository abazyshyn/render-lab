#pragma once

#include <glad/glad.h>

namespace OpenGL
{

    /**
     * @brief Deletes VAO, VBO, IBO
     *
     * @param[in] ct_CountVAO Count of VAO
     * @param[in] ct_VAO pointer to VAO
     * @param[in] ct_CountVBO Count of VBO
     * @param[in] ct_VBO pointer to VBO
     * @param[in] ct_CountIBO Count of IBO
     * @param[in] ct_IBO pointer to IBO
     */
    void DeleteObjects(uint32_t ct_CountVAO, const uint32_t *ct_VAO,
                       uint32_t ct_CountVBO, const uint32_t *ct_VBO,
                       uint32_t ct_CountIBO, const uint32_t *ct_IBO);

#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)

    /**
     * @brief Enables OpenGL debugging
     */
    void EnableDebug();

    /**
     * @brief Callback function that will be called when a debug message is generated
     *
     * @param[in] t_Source Source of a debug message
     * @param[in] t_Type Type of a debug message
     * @param[in] t_Id ID of a debug message
     * @param[in] t_Severity Severity of a debug message
     * @param[in] t_Length Length of debug message
     * @param[in] ct_Message Debug message
     * @param[in] ct_UserParam User defined pointer
     */
    void APIENTRY DebugMessageCallbackOpenGL(GLenum t_Source, GLenum t_Type, GLuint t_Id, GLenum t_Severity, GLsizei t_Length,
                                             const GLchar *ct_Message,
                                             const void *ct_UserParam);

#endif // defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)

} // namespace OpenGL
