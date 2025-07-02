#if !defined(MODEL_HPP)
#define MODEL_HPP

#include "mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Lab
{

    /**
     * @brief Marco for assimp importer flags
     */
#define LAB_ASSIMP_IMPORTER_FLAGS (aiProcess_GenNormals | aiProcess_Triangulate | aiProcess_FlipUVs)

    /**
     * @brief Implementation of a model
     *
     * Controls model
     */
    class CModel
    {
    public:
        explicit CModel(const std::string &ct_ModelPath);

        /**
         * @brief Draws a model.
         *
         * @param[in] ct_Shader Shader program
         */
        void Draw(const CShader &ct_Shader) const;

        /**
         * @brief Returns model name
         *
         * @return Model name
         */
        [[nodiscard]] const std::string &GetName() const { return m_ModelName; }

    private:
        std::vector<CMesh> m_Meshes;
        std::vector<Texture_s> m_LoadedTextures;
        std::string m_ModelDirectory;
        std::string m_ModelName;

        // #if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)
        //         std::string m_ModelName;
        // #endif

        void LoadModel(const std::string &ct_ModelPath);

        void SortTransparentMeshes();

        void ProcessNode(const aiNode *ct_pNode, const aiScene *ct_pScene);

        CMesh ProcessMesh(aiMesh *t_pMesh, const aiScene *ct_pScene);

        std::vector<Texture_s> LoadMaterialTextures(const aiMaterial *ct_pMaterial, aiTextureType ct_TextureType, TextureType_e ct_LocalTextureType);

        uint32_t TextureFromFile(const aiString *ct_TexturePath) const;
    };

} // namespace Lab

#endif // MODEL_HPP
