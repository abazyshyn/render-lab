#include "pch.hpp"

#include "skybox.hpp" // target

#include "renderer/model.hpp"

#include <stb_image.h>
#include <glad/glad.h>

namespace Lab
{

    CSkybox &CSkybox::GetInstance()
    {
        static CSkybox instance;
        return instance;
    }

    CSkybox::CSkybox()
        : CSceneEntity(CModel(Utils::LAB_BASE_MODELS_PATH + "skybox/skybox.fbx")),
          m_Shader(CShader({Utils::LAB_BASE_SHADERS_PATH + "gl_skybox.vert", Utils::LAB_BASE_SHADERS_PATH + "gl_skybox.frag"})),
          m_TextureId(0)
    {
    }

    CSkybox::~CSkybox()
    {
        glDeleteTextures(1, &m_TextureId);
    }

    void CSkybox::BindCubemap() const
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureId);
    }

    void CSkybox::CreateCubemap(const std::array<std::filesystem::path, 6> &ct_CubemapPaths)
    {
        glGenTextures(1, &m_TextureId);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureId);

        int32_t imageWidth = 0, imageHeight = 0, channels = 0;
        for (size_t i = 0; i < 6; ++i)
        {
            unsigned char *pImageData = stbi_load(ct_CubemapPaths[i].string().c_str(), &imageWidth, &imageHeight, &channels, 0);

            if (!pImageData)
            {
                stbi_image_free(pImageData);
                LAB_ERROR_LOG("Failed to load texture pImageData.",
                              "\nTexture: ", ct_CubemapPaths[i].string());
                LAB_ASSERT(0);
                throw std::runtime_error("Failed to load texture pImageData.");
            }

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pImageData);

            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(pImageData);
        }
    }

} // namespace Lab
