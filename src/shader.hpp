#pragma once

namespace Lab
{

    /**
     * @brief Supported shader file types
     */
    enum ShaderType_e
    {
        LAB_SHADER_TYPE_UNKNOWN = 0,
        LAB_SHADER_TYPE_VERTEX,
        LAB_SHADER_TYPE_GEOMETRY,
        LAB_SHADER_TYPE_FRAGMENT
    };

    /**
     * @brief Implementation of a shader program
     *
     * Controls shader program
     */
    class CShader
    {
    public:
        explicit CShader(const std::vector<std::filesystem::path> &shaderPaths);
        ~CShader();

        /**
         * @brief Installs a shader program object as part of current rendering state
         */
        void Bind() const;

        /**
         * @brief Getter for a shader program ID
         *
         * @return Shader program ID
         */
        [[nodiscard]] uint32_t GetProgramId() const { return m_ProgramId; }

        /**
         * @brief Sets float value to the uniform
         *
         * @param[in] uniformName Uniform name
         * @param[in] value Float value
         */
        void SetUniform1f(const std::string &uniformName, float value);

        /**
         * @brief Sets vector of floats of size 3 to the uniform
         *
         * @param[in] uniformName Uniform name
         * @param[in] vector Vector3f
         */
        void SetUniform3fv(const std::string &uniformName, const glm::vec3 &vector);

        /**
         * @brief Sets 3x3 matrix of floats to the uniform
         *
         * @param[in] uniformName Uniform name
         * @param[in] matrix Matrix3f
         */
        void SetUniformMatrix3fv(const std::string &uniformName, const glm::mat3 &matrix);

        /**
         * @brief Sets 4x4 matrix of floats to the uniform
         *
         * @param[in] uniformName Uniform name
         * @param[in] matrix Matrix4f
         */
        void SetUniformMatrix4fv(const std::string &uniformName, const glm::mat4 &matrix);

    private:
#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)
        std::string m_ShaderName;
#endif
        std::unordered_map<std::string, int32_t> m_UniformCache;
        uint32_t m_ProgramId;
        uint32_t m_UBO;

        // unsigned char _pad[4] = {}; // Explicit padding

        void CreateShaderProgramFromSource(const std::vector<std::filesystem::path> &shaderSourcePaths);

        [[nodiscard]] std::string ReadFromSource(const std::string &shaderSourcePath) const;

        void CompileShaderFromSource(ShaderType_e localShaderType, const std::string &shaderSource) const;

        [[nodiscard]] ShaderType_e FindShaderType(const std::string &shaderPath) const;

        [[nodiscard]] int32_t UniformFromCache(const std::string &uniformName);

        static void IsUniformLocationValid(const std::string &uniformName, int32_t uniformLocation);
    };

} // namespace Lab
