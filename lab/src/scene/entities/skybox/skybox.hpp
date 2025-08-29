#if !defined(SKYBOX_HPP)
#define SKYBOX_HPP

#include "scene/entities/scene_entity.hpp"
#include "renderer/shader.hpp"

namespace Lab
{

    /**
     * @brief Implementation of a "skybox"
     *
     * Implemented using Mayers' Singleton pattern
     * Neither CopyConstructible/MoveConstructible nor
     * CopyAssignable/MoveAssignable
     *
     * Controls whole application
     */
    class CSkybox final : public CSceneEntity
    {
    public:
        /**
         * @brief Skybox shader
         */
        CShader m_Shader;

        /**
         * @brief Returns the only one existing instance of the CApplication class
         *
         * @return Instance
         */
        static CSkybox &GetInstance();

        CSkybox(const CSkybox &ct_Source) = delete;
        CSkybox(CSkybox &&t_Source) = delete;

        CSkybox &operator=(const CSkybox &ct_RHV) = delete;
        CSkybox &operator=(CSkybox &&t_RHV) = delete;

        ~CSkybox();

        /**
         * @brief Binds a cube map texture to a texturing target
         */
        void BindCubemap() const;

        /**
         * @brief Creates single cube map texture from 6 separate textures
         *
         * @param[in] ct_CubemapPaths 6 separate textures
         */
        void CreateCubemap(const std::array<std::filesystem::path, 6> &ct_CubemapPaths);

    private:
        uint32_t m_TextureId;
        unsigned char _pad[4] = {}; // Explicit padding

        CSkybox();
    };

} // namespace Lab

#endif // SKYBOX_HPP
