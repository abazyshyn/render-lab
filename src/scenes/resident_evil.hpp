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

        const std::vector<CModel> &GetSceneModels() const override { return m_Models; }

    private:
        std::vector<CModel> m_Models;
        CShader m_DiningRoomShader;
        CFramebuffer m_Framebuffer;
        int32_t m_GuizmoOperation;

        void SetupScene();
    };

} // namespace Lab
