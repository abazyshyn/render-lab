#include "pch.hpp"

#include "opengl.hpp" // target

namespace OpenGL
{

    void DeleteObjects(const uint32_t countVAO, const uint32_t *VAO,
                       const uint32_t countVBO, const uint32_t *VBO,
                       const uint32_t countIBO, const uint32_t *IBO)
    {
        glDeleteVertexArrays(countVAO, VAO);
        glDeleteBuffers(countVBO, VBO);
        glDeleteBuffers(countIBO, IBO);
    }

#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)

    void EnableDebug()
    {
        int32_t contextFlags = 0;
        glGetIntegerv(GL_CONTEXT_FLAGS, &contextFlags);

        // Check if debug context was created
        if (!(contextFlags & GL_CONTEXT_FLAG_DEBUG_BIT))
        {
            LAB_ERROR_LOG("GL_CONTEXT_FLAG_DEBUG_BIT was not created.");
            LAB_ASSERT(0);
        }

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(DebugMessageCallbackOpenGL, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    void DebugMessageCallbackOpenGL(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                    const GLchar *pMessage,
                                    const void *pUserParam)
    {
        std::string strSource;
        std::string strType;
        std::string strSeverity;

        switch (source)
        {
            case GL_DEBUG_SOURCE_API:
            {
                strSource = "API";
                break;
            }
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            {
                strSource = "WINDOW SYSTEM";
                break;
            }
            case GL_DEBUG_SOURCE_SHADER_COMPILER:
            {
                strSource = "SHADER COMPILER";
                break;
            }
            case GL_DEBUG_SOURCE_THIRD_PARTY:
            {
                strSource = "THIRD PARTY";
                break;
            }
            case GL_DEBUG_SOURCE_APPLICATION:
            {
                strSource = "APPLICATION";
                break;
            }
            case GL_DEBUG_SOURCE_OTHER:
            {
                strSource = "UNKNOWN";
                break;
            }
            default:
            {
                strSource = "UNKNOWN";
                break;
            }
        }

        switch (type)
        {
            case GL_DEBUG_TYPE_ERROR:
            {
                strType = "ERROR";
                break;
            }
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            {
                strType = "DEPRECATED BEHAVIOR";
                break;
            }
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            {
                strType = "UDEFINED BEHAVIOR";
                break;
            }
            case GL_DEBUG_TYPE_PORTABILITY:
            {
                strType = "PORTABILITY";
                break;
            }
            case GL_DEBUG_TYPE_PERFORMANCE:
            {
                strType = "PERFORMANCE";
                break;
            }
            case GL_DEBUG_TYPE_OTHER:
            {
                strType = "OTHER";
                break;
            }
            case GL_DEBUG_TYPE_MARKER:
            {
                strType = "MARKER";
                break;
            }
            default:
            {
                strType = "UNKNOWN";
                break;
            }
        }

        switch (severity)
        {
            case GL_DEBUG_SEVERITY_HIGH:
            {
                strSeverity = "HIGH";

                LAB_CRITICAL_LOG("OpenGL Debug Message:\nSource: {0}\nType: {1}\nID: {2}\nSeverity: {3}\nMessage: {4}",
                                 strSource, strType, id, strSeverity, pMessage);
                LAB_ASSERT(0);
                break;
            }
            case GL_DEBUG_SEVERITY_MEDIUM:
            {
                strSeverity = "MEDIUM";
                LAB_ERROR_LOG("OpenGL Debug Message:\nSource: {0}\nType: {1}\nID: {2}\nSeverity: {3}\nMessage: {4}",
                              strSource, strType, id, strSeverity, pMessage);
                LAB_ASSERT(0);
                break;
            }
            case GL_DEBUG_SEVERITY_LOW:
            {
                strSeverity = "LOW";
                LAB_WARN_LOG("OpenGL Debug Message:\nSource: {0}\nType: {1}\nID: {2}\nSeverity: {3}\nMessage: {4}",
                             strSource, strType, id, strSeverity, pMessage);
                break;
            }
            case GL_DEBUG_SEVERITY_NOTIFICATION:
            {
                strSeverity = "NOTIFICATION";
                LAB_INFO_LOG("OpenGL Debug Message:\nSource: {0}\nType: {1}\nID: {2}\nSeverity: {3}\nMessage: {4}",
                             strSource, strType, id, strSeverity, pMessage);
                break;
            }
            default:
            {
                strSeverity = "UNKNOWN";
                LAB_TRACE_LOG("OpenGL Debug Message:\nSource: {0}\nType: {1}\nID: {2}\nSeverity: {3}\nMessage: {4}",
                              strSource, strType, id, strSeverity, pMessage);
                break;
            }
        }
    }

#endif

} // namespace OpenGL
