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
     *
     * Neither CopyConstructible/MoveConstructible nor
     * CopyAssignable/MoveAssignable
     */
    class CScene final : public Utils::CSingleton<CScene>
    {
    public:
        friend class Utils::CSingleton<CScene>;

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
        CShader m_BasicLightingShader;
        // CShader m_DebugNormalShader;
        //  CShader m_ShaderReflect;
        std::vector<std::shared_ptr<CSceneEntity>> m_CommonOpaqueSceneEntities;
        // std::vector<std::shared_ptr<CSceneEntity>> m_ReflectiveObjects;
        // std::vector<std::shared_ptr<CSceneEntity>> m_TransparentSceneEntities;
        std::vector<std::shared_ptr<CSceneEntity>> m_BasicLightingOpaqueSceneEntities;

        CScene();

        void SetupBasicLightingScene();
        void BasicLighting(const glm::mat4 &ct_ViewMatrix);
    };

} // namespace Lab

#endif // SCENE_HPP
