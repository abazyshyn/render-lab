#include "pch.hpp"

#include "opengl.hpp"

namespace OpenGL
{

#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)
    void DeleteObjects(const uint32_t ct_CountVAO, const uint32_t *ct_VAO,
                       const uint32_t ct_CountVBO, const uint32_t *ct_VBO,
                       const uint32_t ct_CountIBO, const uint32_t *ct_IBO)
    {
        glDeleteVertexArrays(ct_CountVAO, ct_VAO);
        glDeleteBuffers(ct_CountVBO, ct_VBO);
        glDeleteBuffers(ct_CountIBO, ct_IBO);
    }

    void EnableDebugOpenGL()
    {
        int32_t contextFlags = 0;
        glGetIntegerv(GL_CONTEXT_FLAGS, &contextFlags);

        // Check if debug context was created
        if (!(contextFlags & GL_CONTEXT_FLAG_DEBUG_BIT))
        {
            LAB_LOG(Lab::LAB_LOG_MESSAGE_SEVERITY_ERROR,
                    "GL_CONTEXT_FLAG_DEBUG_BIT was not created.");
            LAB_ASSERT(0);
        }

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(DebugMessageCallbackOpenGL, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    void DebugMessageCallbackOpenGL(GLenum t_Source, GLenum t_Type, GLuint t_Id, GLenum t_Severity, GLsizei t_Length,
                                    const GLchar *ct_Message,
                                    const void *ct_UserParam)
    {
        std::string source;
        std::string type;
        std::string severity;

        switch (t_Source)
        {
            case GL_DEBUG_SOURCE_API:
            {
                source = "API";
                break;
            }
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            {
                source = "WINDOW SYSTEM";
                break;
            }
            case GL_DEBUG_SOURCE_SHADER_COMPILER:
            {
                source = "SHADER COMPILER";
                break;
            }
            case GL_DEBUG_SOURCE_THIRD_PARTY:
            {
                source = "THIRD PARTY";
                break;
            }
            case GL_DEBUG_SOURCE_APPLICATION:
            {
                source = "APPLICATION";
                break;
            }
            case GL_DEBUG_SOURCE_OTHER:
            {
                source = "UNKNOWN";
                break;
            }
            default:
            {
                source = "UNKNOWN";
                break;
            }
        }

        switch (t_Type)
        {
            case GL_DEBUG_TYPE_ERROR:
            {
                type = "ERROR";
                break;
            }
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            {
                type = "DEPRECATED BEHAVIOR";
                break;
            }
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            {
                type = "UDEFINED BEHAVIOR";
                break;
            }
            case GL_DEBUG_TYPE_PORTABILITY:
            {
                type = "PORTABILITY";
                break;
            }
            case GL_DEBUG_TYPE_PERFORMANCE:
            {
                type = "PERFORMANCE";
                break;
            }
            case GL_DEBUG_TYPE_OTHER:
            {
                type = "OTHER";
                break;
            }
            case GL_DEBUG_TYPE_MARKER:
            {
                type = "MARKER";
                break;
            }
            default:
            {
                type = "UNKNOWN";
                break;
            }
        }

        switch (t_Severity)
        {
            case GL_DEBUG_SEVERITY_HIGH:
            {
                severity = "HIGH";
                break;
            }
            case GL_DEBUG_SEVERITY_MEDIUM:
            {
                severity = "MEDIUM";
                break;
            }
            case GL_DEBUG_SEVERITY_LOW:
            {
                severity = "LOW";
                break;
            }
            case GL_DEBUG_SEVERITY_NOTIFICATION:
            {
                severity = "NOTIFICATION";
                break;
            }
            default:
            {
                severity = "UNKNOWN";
                break;
            }
        }

        LAB_LOG(Lab::LAB_LOG_MESSAGE_SEVERITY_ERROR,
                "OpenGL Debug Message:",
                "\nSource: ", source, "\nType: ", type,
                "\nID: ", t_Id, "\nSeverity: ", severity,
                "\nMessage: ", ct_Message);
        LAB_ASSERT((severity == "HIGH" || severity == "MEDIUM" || severity == "LOW"));
    }

#endif

} // namespace OpenGL
