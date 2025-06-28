#if !defined(SCENE_HPP)
#define SCENE_HPP

#include "renderer/model.hpp"
#include "shader/shader.hpp"

// #include "i_scene_entity.hpp"

namespace Lab
{
    // Forward declaration
    class CWindow;
    class CCamera;

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
        // Temporary test
        CShader shader = CShader({LAB_BASIC_VERTEX_SHADER_PATH, LAB_BASIC_FRAGMENT_SHADER_PATH});
        // Temporary test
        std::vector<CModel> tempModels{CModel("../../../../lab/res/models/bloody_floor/bloody_floor.obj"),
                                       CModel("../../../../lab/res/models/office_window/office_window.obj")};
        // CModel model = CModel("../../../../lab/res/models/floor/bloody-floor.obj");

        // Temporary test
        std::unique_ptr<CCamera> m_pCamera;
        // std::vector<std::unique_ptr<I_CSceneEntity>> m_pSceneEntities;

        CWindow &m_Window;

        CScene();
    };

} // namespace Lab

#endif // SCENE_HPP