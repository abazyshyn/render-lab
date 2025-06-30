#if !defined(SCENE_HPP)
#define SCENE_HPP

#include "scenes/i_scene.hpp"

#include "camera/camera.hpp"
#include "shader/shader.hpp"

namespace Lab
{
    // Forward declaration
    class CWindow;
    class CSceneEntity;

    /**
     * @brief Implementation of the "horror scene"
     */
    class CHorrorScene final : public CIScene
    {
    public:
        CHorrorScene();

        /**
         * @brief Updates a scene entities
         *
         * @param[in] t_DeltaTime Time taken to render last frame
         */
        void OnUpdate(float t_DeltaTime) override;

    private:
        CWindow &m_Window;
        CCamera m_Camera;
        CShader m_Shader;
        std::vector<std::shared_ptr<CSceneEntity>> m_OpaqueSceneEntities;
        std::vector<std::shared_ptr<CSceneEntity>> m_TransparentSceneEntities;
    };

} // namespace Lab

#endif // SCENE_HPP