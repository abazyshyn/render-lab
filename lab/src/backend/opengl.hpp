#if !defined(OPENGL_HPP)
#define OPENGL_HPP

#include <glad/glad.h>

namespace OpenGL
{

    // TODO: wite documentation
    void DeleteObjects(uint32_t ct_CountVAO, const uint32_t *ct_VAO,
                       uint32_t ct_CountVBO, const uint32_t *ct_VBO,
                       uint32_t ct_CountIBO, const uint32_t *ct_IBO);

#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)

    /**
     * @brief Enables OpenGL debugging
     */
    void EnableDebugOpenGL();

    // TODO: wite documentation
    /**
     * @brief Prints debug message to the console if something wrong
     */
    void APIENTRY DebugMessageCallbackOpenGL(GLenum t_Source, GLenum t_Type, GLuint t_Id, GLenum t_Severity, GLsizei t_Length,
                                             const GLchar *ct_Message,
                                             const void *ct_UserParam);

#endif

} // namespace OpenGL

#endif
