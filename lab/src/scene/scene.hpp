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
     * @brief Implementation of the "horror scene"
     */
    class CScene
    {
    public:
        static CScene &GetInstance();

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
        std::vector<std::shared_ptr<CSceneEntity>> m_OpaqueSceneEntities;
        // std::vector<std::shared_ptr<CSceneEntity>> m_ReflectiveObjects;
        // std::vector<std::shared_ptr<CSceneEntity>> m_TransparentSceneEntities;

        CScene();
    };

} // namespace Lab

#endif // SCENE_HPP
