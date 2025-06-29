#if !defined(SCENE_HPP)
#define SCENE_HPP

#include "camera/camera.hpp"
#include "shader/shader.hpp"

namespace Lab
{
    // Forward declaration
    class CWindow;
    class CSceneEntity;

    /**
     * @brief Implementation of the scene
     *
     * Implemented using Mayers' Singleton pattern
     * Neither CopyConstructible/MoveConstructible nor
     * CopyAssignable/MoveAssignable
     *
     * Controls scene
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
        CCamera m_Camera;
        CShader m_Shader;
        std::vector<std::shared_ptr<CSceneEntity>> m_OpaqueSceneEntities;
        std::vector<std::shared_ptr<CSceneEntity>> m_TransparentSceneEntities;

        CScene();
    };

} // namespace Lab

#endif // SCENE_HPP