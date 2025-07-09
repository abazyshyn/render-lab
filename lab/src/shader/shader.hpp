#if !defined(SHADER_HPP)
#define SHADER_HPP

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
        explicit CShader(const std::vector<std::filesystem::path> &ct_ShaderPaths);
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
         * @param[in] ct_UniformName Uniform name
         * @param[in] ct_Value Float value
         */
        void SetUniform1f(const std::string &ct_UniformName, float ct_Value);

        /**
         * @brief Sets vector of floats of size 3 to the uniform
         *
         * @param[in] ct_UniformName Uniform name
         * @param[in] ct_Vector Vector3f
         */
        void SetUniform3fv(const std::string &ct_UniformName, const glm::vec3 &ct_Vector);

        /**
         * @brief Sets 4x4 matrix of floats to the uniform
         *
         * @param[in] ct_UniformName Uniform name
         * @param[in] ct_Matrix Matrix4f
         */
        void SetUniformMatrix4fv(const std::string &ct_UniformName, const glm::mat4 &ct_Matrix);

    private:
#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)
        std::string m_ShaderName;
#endif
        std::unordered_map<std::string, int32_t> m_UniformCache;
        uint32_t m_ProgramId;
        uint32_t m_UBO;

        // unsigned char _pad[4] = {}; // Explicit padding

        void CreateShaderProgramFromSource(const std::vector<std::filesystem::path> &ct_ShaderSourcePaths);

        [[nodiscard]] std::string ReadFromSource(const std::string &ct_ShaderSourcePath) const;

        void CompileShaderFromSource(ShaderType_e ct_LocalShaderType, const std::string &ct_ShaderSource) const;

        [[nodiscard]] ShaderType_e FindShaderType(const std::string &ct_ShaderPath) const;

        [[nodiscard]] int32_t UniformFromCache(const std::string &ct_UniformName);

        static void IsUniformLocationValid(const std::string &ct_UniformName, int32_t ct_UniformLocation);
    };

} // namespace Lab

#endif // SHADER_HPP
