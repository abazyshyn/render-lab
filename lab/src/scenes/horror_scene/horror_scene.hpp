#if !defined(SCENE_HPP)
#define SCENE_HPP

#include "scenes/i_scene.hpp"
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
    class CHorrorScene final : public CIScene
    {
    public:
        // TODO: Should it be a singleton?
        CHorrorScene();

        /**
         * @brief Updates a scene entities
         *
         * @param[in] t_DeltaTime Time taken to render last frame
         */
        void OnUpdate(float t_DeltaTime) override;

    private:
        CWindow &m_Window;
        CSkybox &m_Skybox;
        CCamera m_Camera;
        CUniformBuffer m_UBO;
        CShader m_Shader;
        CShader m_DebugNormalShader;
        CShader m_ShaderReflect;
        std::vector<std::shared_ptr<CSceneEntity>> m_OpaqueSceneEntities;
        std::vector<std::shared_ptr<CSceneEntity>> m_ReflectiveObjects;
        std::vector<std::shared_ptr<CSceneEntity>> m_TransparentSceneEntities;
    };

} // namespace Lab

#endif // SCENE_HPP
