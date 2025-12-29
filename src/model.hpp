#pragma once

#include "mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Lab
{

    /**
     * @brief Marco for assimp importer flags
     */
#define LAB_ASSIMP_IMPORTER_FLAGS aiProcess_GenNormals | aiProcess_Triangulate | aiProcess_FlipUVs

    /**
     * @brief Implementation of a model
     *
     * Controls model
     */
    class CModel
    {
    public:
        explicit CModel(const std::string &modelPath);

        /**
         * @brief Draws a model.
         *
         * @param[in] shader Shader program
         */
        void Draw(CShader &shader) const;

        /**
         * @brief Returns model name
         *
         * @return Model name
         */
        [[nodiscard]] const std::string &GetName() const { return m_ModelName; }

        /**
         * @brief Returns model matrix
         *
         * @return Model matrix
         */
        [[nodiscard]] const glm::mat4 &GetModelMatrix() const { return m_ModelMatrix; }

        /**
         * @brief Sets the model matrix
         *
         * @param[in] matrix Matrix
         */
        void SetModelMatrix(const glm::mat4 &matrix) { m_ModelMatrix = matrix; }

    private:
        glm::mat4 m_ModelMatrix;
        std::vector<CMesh> m_Meshes;
        std::vector<Texture_s> m_LoadedTextures;
        std::string m_ModelDirectory;
        std::string m_ModelName;

        // TODO: decide what to do about this
        // #if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)
        //         std::string m_ModelName;
        // #endif

        void LoadModel(const std::string &modelPath);

        void SortTransparentMeshes();

        void ProcessNode(const aiNode *pNode, const aiScene *pScene);

        CMesh ProcessMesh(aiMesh *pMesh, const aiScene *pScene);

        std::vector<Texture_s> LoadMaterialTextures(const aiMaterial *pMaterial, aiTextureType textureType, TextureType_e localTextureType);

        uint32_t TextureFromFile(const aiString *texturePath) const;
    };

} // namespace Lab
