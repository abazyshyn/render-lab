#include "pch.hpp"

#include "shader.hpp"
#include <glad/glad.h>

namespace Lab
{

    CShader::CShader(const std::vector<std::filesystem::path> &ct_ShaderPaths)
        : m_ProgramId()
    {
        CreateShaderProgramFromSource(ct_ShaderPaths);
    }

    CShader::~CShader()
    {
        glDeleteProgram(m_ProgramId);
    }

    void CShader::Bind() const
    {
        glUseProgram(m_ProgramId);
    }

    void CShader::SetUniformMatrix4fv(const std::string &ct_UniformName, const glm::mat4 &ct_Matrix)
    {
        const int32_t uniformLocation = UniformFromCache(ct_UniformName);

        LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_WARNING,
                "Setting the uniform matrix4fv...",
                "\nUniform name: ", ct_UniformName,
                "\nLocation: ", uniformLocation);

        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(ct_Matrix));
    }

    void CShader::CreateShaderProgramFromSource(const std::vector<std::filesystem::path> &ct_ShaderSourcePaths)
    {
        m_ProgramId = glCreateProgram();

        for (const std::filesystem::path &shaderSourcePath : ct_ShaderSourcePaths)
        {
            const std::string path = shaderSourcePath.string();

#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)
            m_ShaderName = path.substr(path.find_last_of('/') + 1, path.find_last_of('.'));

            LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_SOFT,
                    "Processing the shader...\n",
                    m_ShaderName);
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

            LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_ERROR,
                    "Shader program linking error.",
                    "\nMessage: ", pErrorMessage);

            LAB_ASSERT(0);
        }
#endif
    }

    std::string CShader::ReadFromSource(const std::string &ct_ShaderSourcePath) const
    {
        std::ifstream file(ct_ShaderSourcePath);

        /**
         * Check if file open only in Debug build because
         * game must to work correctly in Release build
         */
#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)
        if (!file.is_open())
        {
            LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_ERROR,
                    "Failed to open the source.",
                    "\nShader source: ", m_ShaderName);
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
            LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_ERROR,
                    "Failed to close the source.",
                    "\nShader source: ", m_ShaderName);
            LAB_ASSERT(file.is_open());
        }
#endif

        return ss.str();
    }

    void CShader::CompileShaderFromSource(const ShaderType_e ct_LocalShaderType, const std::string &ct_ShaderSource) const
    {
        GLenum shaderType{};
        switch (ct_LocalShaderType)
        {
            case LAB_SHADER_TYPE_VERTEX:
            {
                shaderType = GL_VERTEX_SHADER;
                break;
            }
            case LAB_SHADER_TYPE_FRAGMENT:
            {
                shaderType = GL_FRAGMENT_SHADER;
                break;
            }
            default:
            {
                LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_ERROR,
                        "Detected unsupported shader type.");
                LAB_ASSERT(0);
            }
        }

        const uint32_t shaderId = glCreateShader(shaderType);
        const char *pShaderSource = ct_ShaderSource.c_str();
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

            LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_ERROR,
                    (shaderType == GL_VERTEX_SHADER ? "Vertex shader" : "Fragment shader"),
                    " failed to compile.",
                    "\nShader source: ", m_ShaderName,
                    "\nMessage: ", pErrorMessage);

            LAB_ASSERT(0);
        }
#endif

        glAttachShader(m_ProgramId, shaderId);
        glDeleteShader(shaderId);
    }

    ShaderType_e CShader::FindShaderType(const std::string &ct_ShaderPath) const
    {
        if (ct_ShaderPath.find(".vert") != std::string::npos)
        {
            return LAB_SHADER_TYPE_VERTEX;
        }
        else if (ct_ShaderPath.find(".frag") != std::string::npos)
        {
            return LAB_SHADER_TYPE_FRAGMENT;
        }
        else
        {
            LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_ERROR,
                    "Failed to create shader program.",
                    "\nUnknown shader type was detected.\n",
                    m_ShaderName);
            LAB_ASSERT(0);
        }

        /**
         * Since last "else" part won't appear in Release build
         * function must return unknown shader type
         */
        return LAB_SHADER_TYPE_UNKNOWN;
    }

    int32_t CShader::UniformFromCache(const std::string &ct_UniformName)
    {
        /**
         * Check uniform location in cache
         */
        if (m_UniformCache.find(ct_UniformName) != m_UniformCache.end())
        {
            return m_UniformCache[ct_UniformName];
        }

        const int32_t uniformLocation = glGetUniformLocation(m_ProgramId, ct_UniformName.c_str());
        IsUniformLocationValid(ct_UniformName, uniformLocation);

        return m_UniformCache[ct_UniformName] = uniformLocation;
    }

    void CShader::IsUniformLocationValid(const std::string &ct_UniformName, const int32_t ct_UniformLocation)
    {
        if (ct_UniformLocation == -1)
        {
            LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_ERROR,
                    "Shader uniform cannot find the location.",
                    "\nUniform name: ", ct_UniformName);
            LAB_ASSERT(0);
            throw std::runtime_error("Shader uniform cannot find the location.");
        }
    }

} // namespace Lab
