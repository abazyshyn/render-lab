#pragma once

#include <glad/glad.h>

namespace OpenGL
{

    /**
     * @brief Deletes VAO, VBO, IBO
     *
     * @param[in] countVAO Count of VAO
     * @param[in] VAO pointer to VAO
     * @param[in] countVBO Count of VBO
     * @param[in] VBO pointer to VBO
     * @param[in] countIBO Count of IBO
     * @param[in] IBO pointer to IBO
     */
    void DeleteObjects(uint32_t countVAO, const uint32_t *VAO,
                       uint32_t countVBO, const uint32_t *VBO,
                       uint32_t countIBO, const uint32_t *IBO);

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
     * @param[in] Message Debug message
     * @param[in] UserParam User defined pointer
     */
    void APIENTRY DebugMessageCallbackOpenGL(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                             const GLchar *pMessage,
                                             const void *pUserParam);

#endif // defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)

} // namespace OpenGL
