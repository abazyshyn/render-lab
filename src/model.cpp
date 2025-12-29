#include "pch.hpp"

#include "shader.hpp"
#include "model.hpp"
#include <stb_image.h>
#include <glad/glad.h>

namespace Lab
{

    CModel::CModel(const std::string &modelPath)
        : m_ModelMatrix(1.0f)
    {
        LoadModel(modelPath);
    }

    void CModel::Draw(CShader &shader) const
    {
        LAB_TRACE_LOG("Drawing model...\nModel name: {0}", m_ModelName);

        for (const CMesh &mesh : m_Meshes)
        {
            mesh.Draw(shader);
        }
    }

    void CModel::LoadModel(const std::string &modelPath)
    {
        m_ModelDirectory = modelPath.substr(0, modelPath.find_last_of('/'));

#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)
        m_ModelName = modelPath.substr(modelPath.find_last_of('/') + 1);
#endif

        LAB_TRACE_LOG("Loading model...\nModel name: {0}", m_ModelName);

        Assimp::Importer importer;

        const aiScene *pScene = importer.ReadFile(modelPath.c_str(), LAB_ASSIMP_IMPORTER_FLAGS);

        if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode)
        {
            LAB_ERROR_LOG("Failed to load aiScene.");
            LAB_ASSERT(0);
            throw std::runtime_error("Failed to load aiScene.");
        }

        ProcessNode(pScene->mRootNode, pScene);
        SortTransparentMeshes();
    }

    void CModel::SortTransparentMeshes()
    {
        // Implementation of a compare functor
        // Acts like compare function for std::sort
        constexpr struct
        {
            // Operator overloading
            // Compare function for std::sort
            bool operator()(const CMesh &ct_A, const CMesh &ct_B) const
            {
                // Returning only "ct_A.GetName().find("glass") == std::string::npos" works with some implementations
                // but with MSVC it is "Invalid comparator"
                return ct_A.GetName().find("glass") == std::string::npos && ct_B.GetName().find("glass") != std::string::npos;
            }
        } CompareFn;

        std::sort(m_Meshes.begin(), m_Meshes.end(), CompareFn);
    }

    void CModel::ProcessNode(const aiNode *pNode, const aiScene *pScene)
    {
        for (size_t i = 0; i < pNode->mNumMeshes; ++i)
        {
            aiMesh *mesh = pScene->mMeshes[pNode->mMeshes[i]];
            m_Meshes.emplace_back(ProcessMesh(mesh, pScene));
        }

        for (size_t i = 0; i < pNode->mNumChildren; ++i)
        {
            ProcessNode(pNode->mChildren[i], pScene);
        }
    }

    CMesh CModel::ProcessMesh(aiMesh *pMesh, const aiScene *pScene)
    {
        LAB_TRACE_LOG("Processing mesh...\nMesh: {0}", pMesh->mName.C_Str());

        std::vector<Vertex_s> vertices{};
        std::vector<uint32_t> indices{};
        std::vector<Texture_s> textures{};

        // Process positions
        LAB_TRACE_LOG("Processing mesh vertex positions...\nMesh: {0}", pMesh->mName.C_Str());
        for (size_t i = 0; i < pMesh->mNumVertices; ++i)
        {
            Vertex_s vertex{};

            glm::vec3 v3Placeholder(0.0f);
            v3Placeholder.x = pMesh->mVertices[i].x;
            v3Placeholder.y = pMesh->mVertices[i].y;
            v3Placeholder.z = pMesh->mVertices[i].z;
            vertex.m_PositionVector = v3Placeholder;

            if (pMesh->HasNormals())
            {
                v3Placeholder.x = pMesh->mNormals[i].x;
                v3Placeholder.y = pMesh->mNormals[i].y;
                v3Placeholder.z = pMesh->mNormals[i].z;
                vertex.m_NormalVector = v3Placeholder;
            }

            if (pMesh->mTextureCoords[0])
            {
                glm::vec2 v2Placeholder(0.0f);
                v2Placeholder.x = pMesh->mTextureCoords[0][i].x;
                v2Placeholder.y = pMesh->mTextureCoords[0][i].y;
                vertex.m_TextureCoordinatesVector = v2Placeholder;
            }
            else
            {
                vertex.m_TextureCoordinatesVector = glm::vec2(0.0f, 0.0f);
            }

            vertices.emplace_back(vertex);
        }

        // Process indices
        LAB_TRACE_LOG("Processing mesh indices...\nMesh: {0}", pMesh->mName.C_Str());
        for (size_t i = 0; i < pMesh->mNumFaces; ++i)
        {
            aiFace face = pMesh->mFaces[i];

            for (size_t j = 0; j < face.mNumIndices; ++j)
            {
                indices.emplace_back(face.mIndices[j]);
            }
        }

        // Process textures(materials)
        LAB_TRACE_LOG("Processing mesh textures...\nMesh: {0}", pMesh->mName.C_Str());

        aiMaterial *pMaterial = pScene->mMaterials[pMesh->mMaterialIndex];

        std::vector<Texture_s> diffuseMaps = LoadMaterialTextures(pMaterial,
                                                                  aiTextureType_DIFFUSE,
                                                                  LAB_TEXTURE_TYPE_DIFFUSE);
        std::vector<Texture_s> specularMaps = LoadMaterialTextures(pMaterial,
                                                                   aiTextureType_METALNESS,
                                                                   LAB_TEXTURE_TYPE_SPECULAR);

        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        LAB_TRACE_LOG("Mesh processed.\nMesh: {0}", pMesh->mName.C_Str());

        return CMesh(vertices, indices, textures, pMesh->mName.C_Str());
    }

    std::vector<Texture_s> CModel::LoadMaterialTextures(const aiMaterial *pMaterial,
                                                        const aiTextureType textureType,
                                                        const TextureType_e localTextureType)
    {
        std::vector<Texture_s> textures{};

        for (size_t i = 0; i < pMaterial->GetTextureCount(textureType); ++i)
        {
            aiString texturePath{};
            pMaterial->GetTexture(textureType, i, &texturePath);

            LAB_TRACE_LOG("Loading texture\nTexture: {0}", texturePath.C_Str());

            bool skipTextureLoading = false;
            for (const Texture_s &loadedTexture : m_LoadedTextures)
            {
                if (strcmp(loadedTexture.m_TexturePath.c_str(), texturePath.C_Str()) == 0)
                {
                    textures.emplace_back(loadedTexture);
                    skipTextureLoading = true;
                    break;
                }
            }

            if (skipTextureLoading)
            {
                continue;
            }

            Texture_s texture;

            texture.m_TexturePath = texturePath.C_Str();
            texture.m_TextureType = localTextureType;
            texture.m_TextureId = TextureFromFile(&texturePath);

            m_LoadedTextures.emplace_back(texture);
            textures.emplace_back(texture);
        }

        return textures;
    }

    uint32_t CModel::TextureFromFile(const aiString *texturePath) const
    {
        std::string fileName = texturePath->C_Str();
        fileName = m_ModelDirectory + "/" + fileName;

        uint32_t textureId = 0;
        glGenTextures(1, &textureId);

        int32_t imageWidth = 0, imageHeight = 0, channels = 0;
        unsigned char *pImageData = stbi_load(fileName.c_str(), &imageWidth, &imageHeight, &channels, 0);

        if (!pImageData)
        {
            stbi_image_free(pImageData);
            LAB_ERROR_LOG("Failed to load texture pImageData.\nTexture: {0}", fileName);
            LAB_ASSERT(0);
            throw std::runtime_error("Failed to load texture pImageData.");
        }

        GLint textureFormat;
        switch (channels)
        {
            case 1:
            {
                textureFormat = GL_RED;
                break;
            }
            case 3:
            {
                textureFormat = GL_RGB;
                break;
            }
            case 4:
            {
                textureFormat = GL_RGBA;
                break;
            }
            default:
            {
                LAB_ERROR_LOG("Unsupported texture format.");
                LAB_ASSERT(0);
            }
        }

        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, imageWidth, imageHeight, 0, textureFormat, GL_UNSIGNED_BYTE, pImageData);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(pImageData);

        return textureId;
    }

} // namespace Lab
