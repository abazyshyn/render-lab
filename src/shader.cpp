#include "pch.hpp"

#include "shader.hpp"
#include <glad/glad.h>

namespace Lab
{

    CShader::CShader(const std::vector<std::filesystem::path> &shaderPaths)
        : m_ProgramId()
    {
        CreateShaderProgramFromSource(shaderPaths);
    }

    CShader::~CShader()
    {
        glDeleteProgram(m_ProgramId);
    }

    void CShader::Bind() const
    {
        glUseProgram(m_ProgramId);
    }

    void CShader::SetUniform1f(const std::string &uniformName, const float value)
    {
        const int32_t uniformLocation = UniformFromCache(uniformName);

        LAB_TRACE_LOG("Setting the uniform 1f:\nUniform name: {0}\nLocation: {1}",
                      uniformName, uniformLocation);

        glUniform1f(uniformLocation, value);
    }

    void CShader::SetUniform3fv(const std::string &uniformName, const glm::vec3 &vector)
    {
        const int32_t uniformLocation = UniformFromCache(uniformName);

        LAB_TRACE_LOG("Setting the uniform 3fv:\nUniform name: {0}\nLocation: {1}",
                      uniformName, uniformLocation);

        glUniform3fv(uniformLocation, 1, glm::value_ptr(vector));
    }

    void CShader::SetUniformMatrix3fv(const std::string &uniformName, const glm::mat3 &matrix)
    {
        const int32_t uniformLocation = UniformFromCache(uniformName);

        LAB_TRACE_LOG("Setting the uniform matrix3fv:\nUniform name: {0}\nLocation: {1}",
                      uniformName, uniformLocation);

        glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void CShader::SetUniformMatrix4fv(const std::string &uniformName, const glm::mat4 &matrix)
    {
        const int32_t uniformLocation = UniformFromCache(uniformName);

        LAB_TRACE_LOG("Setting the uniform matrix4fv:\nUniform name: {0}\nLocation: {1}",
                      uniformName, uniformLocation);

        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void CShader::CreateShaderProgramFromSource(const std::vector<std::filesystem::path> &shaderSourcePaths)
    {
        m_ProgramId = glCreateProgram();

        for (const std::filesystem::path &shaderSourcePath : shaderSourcePaths)
        {
            const std::string path = shaderSourcePath.string();

#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)
            m_ShaderName = path.substr(path.find_last_of('/') + 1, path.find_last_of('.'));

            LAB_TRACE_LOG("Processing the shader: {0}", m_ShaderName);
#endif

            std::string shaderSource = ReadFromSource(path);
            CompileShaderFromSource(FindShaderType(path), shaderSource);
        }

        glLinkProgram(m_ProgramId);

        /**
         * Check if shader program linked only in Debug build because
         * game must to work correctly in Release build
         */
#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)
        int32_t programLinkStatus;
        glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &programLinkStatus);
        if (programLinkStatus != GL_TRUE)
        {
            int32_t messageLength;
            glGetProgramiv(m_ProgramId, GL_INFO_LOG_LENGTH, &messageLength);

            char *pErrorMessage = static_cast<char *>(alloca(messageLength * sizeof(char)));
            glGetProgramInfoLog(m_ProgramId, messageLength, &messageLength, pErrorMessage);

            LAB_ERROR_LOG("Shader program linking error.\nMessage: {0}", pErrorMessage);

            LAB_ASSERT(0);
        }
#endif
    }

    std::string CShader::ReadFromSource(const std::string &shaderSourcePath) const
    {
        std::ifstream file(shaderSourcePath);

        /**
         * Check if file open only in Debug build because
         * game must to work correctly in Release build
         */
#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)
        if (!file.is_open())
        {
            LAB_ERROR_LOG("Failed to open the source.\nShader source: {0}", m_ShaderName);
            LAB_ASSERT(!file.is_open());
        }
#endif

        std::string currentLine{};
        std::stringstream ss{};
        for (; getline(file, currentLine);)
        {
            ss << currentLine << '\n';
        }

        file.close();

        /**
         * Check if file closed only in Debug build because
         * game must to work correctly in Release build
         */
#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)
        if (file.is_open())
        {
            LAB_ERROR_LOG("Failed to close the source.\nShader source: {0}", m_ShaderName);
            LAB_ASSERT(file.is_open());
        }
#endif

        return ss.str();
    }

    void CShader::CompileShaderFromSource(const ShaderType_e localShaderType, const std::string &shaderSource) const
    {
        GLenum shaderType{};
        switch (localShaderType)
        {
            case LAB_SHADER_TYPE_VERTEX:
            {
                shaderType = GL_VERTEX_SHADER;
                break;
            }
            case LAB_SHADER_TYPE_GEOMETRY:
            {
                shaderType = GL_GEOMETRY_SHADER;
                break;
            }
            case LAB_SHADER_TYPE_FRAGMENT:
            {
                shaderType = GL_FRAGMENT_SHADER;
                break;
            }
            default:
            {
                LAB_ERROR_LOG("Detected unsupported shader type.");
                LAB_ASSERT(0);
            }
        }

        const uint32_t shaderId = glCreateShader(shaderType);
        const char *pShaderSource = shaderSource.c_str();
        glShaderSource(shaderId, 1, &pShaderSource, nullptr);
        glCompileShader(shaderId);

        /**
         * Check if shader compiled only in Debug build because
         * game must to work correctly in Release build
         */
#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)
        int32_t compileStatus;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);
        if (GL_TRUE != compileStatus)
        {
            int32_t messageLength;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &messageLength);

            char *pErrorMessage = static_cast<char *>(alloca(messageLength * sizeof(char)));
            glGetShaderInfoLog(shaderId, messageLength, &messageLength, pErrorMessage);

            LAB_ERROR_LOG("{0} failed to compile.\nShader source: {1}\nMessage: {2}",
                          (shaderType == GL_VERTEX_SHADER ? "Vertex shader" : "Fragment shader"),
                          m_ShaderName, pErrorMessage);

            LAB_ASSERT(0);
        }
#endif

        glAttachShader(m_ProgramId, shaderId);
        glDeleteShader(shaderId);
    }

    ShaderType_e CShader::FindShaderType(const std::string &shaderPath) const
    {
        if (shaderPath.find(".vert") != std::string::npos)
        {
            return LAB_SHADER_TYPE_VERTEX;
        }
        else if (shaderPath.find(".geom") != std::string::npos)
        {
            return LAB_SHADER_TYPE_GEOMETRY;
        }
        else if (shaderPath.find(".frag") != std::string::npos)
        {
            return LAB_SHADER_TYPE_FRAGMENT;
        }
        else
        {
            LAB_ERROR_LOG("Failed to create shader program.\nUnknown shader type: {0}", m_ShaderName);
            LAB_ASSERT(0);
        }

        /**
         * Since last "else" part won't appear in Release build
         * function must return unknown shader type
         */
        return LAB_SHADER_TYPE_UNKNOWN;
    }

    int32_t CShader::UniformFromCache(const std::string &uniformName)
    {
        /**
         * Check uniform location in cache
         */
        if (m_UniformCache.find(uniformName) != m_UniformCache.end())
        {
            return m_UniformCache[uniformName];
        }

        const int32_t uniformLocation = glGetUniformLocation(m_ProgramId, uniformName.c_str());
        IsUniformLocationValid(uniformName, uniformLocation);

        return m_UniformCache[uniformName] = uniformLocation;
    }

    void CShader::IsUniformLocationValid(const std::string &uniformName, const int32_t uniformLocation)
    {
        if (uniformLocation == -1)
        {
            LAB_ERROR_LOG("Shader uniform cannot find the location.\nUniform name: {0}", uniformName);
            LAB_ASSERT(0);
            throw std::runtime_error("Shader uniform cannot find the location.");
        }
    }

} // namespace Lab
