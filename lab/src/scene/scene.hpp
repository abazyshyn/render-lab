#if !defined(SCENE_HPP)
#define SCENE_HPP

#include "camera/camera.hpp"
#include "shader/shader.hpp"
#include "buffers/uniform_buffer.hpp"

namespace Lab
{
    // Forward declaration
    class CWindow;
    class CSkybox;
    class CSceneEntity;

    /**
     * @brief Implementation of the "scene"
     *
     * Holds entities and renders them
     *
     * Implemented using Mayers' Singleton pattern
     * Neither CopyConstructible/MoveConstructible nor
     * CopyAssignable/MoveAssignable
     */
    class CScene
    {
    public:
        /**
         * @brief Returns the only one existing instance of the CScene class
         *
         * @return Instance
         */
        static CScene &GetInstance();

        CScene(const CScene &ct_Source) = delete;
        CScene(CScene &&t_Source) = delete;

        CScene &operator=(const CScene &ct_RHV) = delete;
        CScene &operator=(CScene &&t_RHV) = delete;

        /**
         * @brief Updates a scene entities
         *
         * @param[in] t_DeltaTime Time taken to render last frame
         */
        void OnUpdate(float t_DeltaTime);

    private:
        CWindow &m_Window;
        CSkybox &m_Skybox;
        CCamera m_Camera;
        CUniformBuffer m_UBO;
        CShader m_SceneShader;
        CShader m_BasicShader; // TODO: temp
        // CShader m_DebugNormalShader;
        //  CShader m_ShaderReflect;
        std::vector<std::shared_ptr<CSceneEntity>> m_CommonOpaqueSceneEntities;
        // std::vector<std::shared_ptr<CSceneEntity>> m_ReflectiveObjects;
        // std::vector<std::shared_ptr<CSceneEntity>> m_TransparentSceneEntities;
        std::vector<std::shared_ptr<CSceneEntity>> m_BasicLightingOpaqueSceneEntities;

        CScene();

        void BasicLighting();
    };

} // namespace Lab

#endif // SCENE_HPP
