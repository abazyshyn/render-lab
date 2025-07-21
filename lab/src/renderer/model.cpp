#include "pch.hpp"

#include "shader/shader.hpp"

#include "model.hpp" // target
#include <stb_image.h>
#include <glad/glad.h>

namespace Lab
{

    CModel::CModel(const std::string &ct_ModelPath)
    {
        LoadModel(ct_ModelPath);
    }

    void CModel::Draw(CShader &ct_Shader) const
    {
        LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_SOFT,
                "Drawing model...",
                "\nModel name:", m_ModelName);

        for (const CMesh &mesh : m_Meshes)
        {
            mesh.Draw(ct_Shader);
        }
    }

    void CModel::LoadModel(const std::string &ct_ModelPath)
    {
        m_ModelDirectory = ct_ModelPath.substr(0, ct_ModelPath.find_last_of('/'));

#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)
        m_ModelName = ct_ModelPath.substr(ct_ModelPath.find_last_of('/') + 1);
#endif

        LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_SOFT,
                "Loading model...",
                "\nModel name:", m_ModelName);

        Assimp::Importer importer;

        const aiScene *pScene = importer.ReadFile(ct_ModelPath.c_str(), LAB_ASSIMP_IMPORTER_FLAGS);

        if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode)
        {
            LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_ERROR, "Failed to load aiScene.");
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
        } CompareFn_s;

        std::sort(m_Meshes.begin(), m_Meshes.end(), CompareFn_s);
    }

    void CModel::ProcessNode(const aiNode *ct_pNode, const aiScene *ct_pScene)
    {
        for (size_t i = 0; i < ct_pNode->mNumMeshes; ++i)
        {
            aiMesh *mesh = ct_pScene->mMeshes[ct_pNode->mMeshes[i]];
            m_Meshes.emplace_back(ProcessMesh(mesh, ct_pScene));
        }

        for (size_t i = 0; i < ct_pNode->mNumChildren; ++i)
        {
            ProcessNode(ct_pNode->mChildren[i], ct_pScene);
        }
    }

    CMesh CModel::ProcessMesh(aiMesh *t_pMesh, const aiScene *ct_pScene)
    {
        LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_SOFT,
                "Processing mesh...",
                "\nMesh:", t_pMesh->mName.C_Str());

        std::vector<Vertex_s> vertices{};
        std::vector<uint32_t> indices{};
        std::vector<Texture_s> textures{};

        // Process positions
        LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_SOFT,
                "Processing mesh vertex positions...",
                "\nMesh:", t_pMesh->mName.C_Str());
        for (size_t i = 0; i < t_pMesh->mNumVertices; ++i)
        {
            Vertex_s vertex{};

            glm::vec3 v3Placeholder(0.0f);
            v3Placeholder.x = t_pMesh->mVertices[i].x;
            v3Placeholder.y = t_pMesh->mVertices[i].y;
            v3Placeholder.z = t_pMesh->mVertices[i].z;
            vertex.m_PositionVector = v3Placeholder;

            if (t_pMesh->HasNormals())
            {
                v3Placeholder.x = t_pMesh->mNormals[i].x;
                v3Placeholder.y = t_pMesh->mNormals[i].y;
                v3Placeholder.z = t_pMesh->mNormals[i].z;
                vertex.m_NormalVector = v3Placeholder;
            }

            if (t_pMesh->mTextureCoords[0])
            {
                glm::vec2 v2Placeholder(0.0f);
                v2Placeholder.x = t_pMesh->mTextureCoords[0][i].x;
                v2Placeholder.y = t_pMesh->mTextureCoords[0][i].y;
                vertex.m_TextureCoordinatesVector = v2Placeholder;
            }
            else
            {
                vertex.m_TextureCoordinatesVector = glm::vec2(0.0f, 0.0f);
            }

            vertices.emplace_back(vertex);
        }

        // Process indices
        LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_SOFT,
                "Processing mesh indices...",
                "\nMesh:", t_pMesh->mName.C_Str());
        for (size_t i = 0; i < t_pMesh->mNumFaces; ++i)
        {
            aiFace face = t_pMesh->mFaces[i];

            for (size_t j = 0; j < face.mNumIndices; ++j)
            {
                indices.emplace_back(face.mIndices[j]);
            }
        }

        // Process textures(materials)
        LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_SOFT,
                "Processing mesh textures...",
                "\nMesh:", t_pMesh->mName.C_Str());

        aiMaterial *pMaterial = ct_pScene->mMaterials[t_pMesh->mMaterialIndex];

        std::vector<Texture_s> diffuseMaps = LoadMaterialTextures(pMaterial,
                                                                  aiTextureType_DIFFUSE,
                                                                  LAB_TEXTURE_TYPE_DIFFUSE);
        std::vector<Texture_s> specularMaps = LoadMaterialTextures(pMaterial,
                                                                   aiTextureType_SPECULAR,
                                                                   LAB_TEXTURE_TYPE_SPECULAR);

        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_WARNING,
                "Mesh processed.",
                "\nMesh:", t_pMesh->mName.C_Str());

        return CMesh(vertices, indices, textures, t_pMesh->mName.C_Str());
    }

    std::vector<Texture_s> CModel::LoadMaterialTextures(const aiMaterial *ct_pMaterial,
                                                        const aiTextureType ct_TextureType,
                                                        const TextureType_e ct_LocalTextureType)
    {
        std::vector<Texture_s> textures{};

        for (size_t i = 0; i < ct_pMaterial->GetTextureCount(ct_TextureType); ++i)
        {
            aiString texturePath{};
            ct_pMaterial->GetTexture(ct_TextureType, i, &texturePath);

            LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_SOFT,
                    "Loading texture",
                    "\nTexture:", texturePath.C_Str());

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

            if (ct_LocalTextureType == LAB_TEXTURE_TYPE_SPECULAR)
            {
                float shininess = 0.0f;
                ct_pMaterial->Get(AI_MATKEY_SHININESS, shininess);
                texture.m_Shininess = shininess;
            }

            texture.m_TexturePath = texturePath.C_Str();
            texture.m_TextureType = ct_LocalTextureType;
            texture.m_TextureId = TextureFromFile(&texturePath);

            m_LoadedTextures.emplace_back(texture);
            textures.emplace_back(texture);
        }

        return textures;
    }

    uint32_t CModel::TextureFromFile(const aiString *ct_TexturePath) const
    {
        std::string fileName = ct_TexturePath->C_Str();
        fileName = m_ModelDirectory + "/" + fileName;

        uint32_t textureId = 0;
        glGenTextures(1, &textureId);

        int32_t imageWidth = 0, imageHeight = 0, channels = 0;
        unsigned char *pImageData = stbi_load(fileName.c_str(), &imageWidth, &imageHeight, &channels, 0);

        if (!pImageData)
        {
            stbi_image_free(pImageData);
            LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_ERROR,
                    "Failed to load texture pImageData.",
                    "\nTexture: ", fileName);
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
                LAB_LOG(LAB_LOG_MESSAGE_SEVERITY_ERROR,
                        "Unsupported texture format.");
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
