#if !defined(OPENGL_HPP)
#define OPENGL_HPP

namespace Lab
{

#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)

    /**
     * @brief Enables OpenGL debugging
     */
    void EnableDebugOpenGL();

    /**
     * @brief Prints debug message to the console if something wrong
     */
    void APIENTRY DebugMessageCallbackOpenGL(GLenum t_Source, GLenum t_Type,
                                             GLuint t_Id, GLenum t_Severity,
                                             GLsizei t_Length,
                                             const GLchar *ct_Message,
                                             const void *ct_UserParam);

#endif

} // namespace Lab

#endif
