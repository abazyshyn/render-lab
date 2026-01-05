#pragma once

#include "scene.hpp"
#include "shader.hpp"
#include "framebuffer.hpp"

namespace Lab
{

    class CResidentEvilScene : public CScene
    {
    public:
        CResidentEvilScene();

        CResidentEvilScene(const CResidentEvilScene &source) = delete;
        CResidentEvilScene &operator=(const CResidentEvilScene &source) = delete;

        CResidentEvilScene(CResidentEvilScene &&source) noexcept;
        CResidentEvilScene &operator=(CResidentEvilScene &&source) noexcept;

        void OnUpdate(float deltaTime, CCamera &camera, CWindow &window) override;

        void DrawModelGuizmo(CWindow &window, CModel &model, glm::mat4 &modelMatrix, glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);

        std::vector<CModel> &GetSceneModels() override { return m_Models; }

    private:
        std::vector<CModel> m_Models;
        CShader m_DiningRoomShader;
        CFramebuffer m_Framebuffer;
        int32_t m_GuizmoOperation;

        void SetupScene();
    };

} // namespace Lab
