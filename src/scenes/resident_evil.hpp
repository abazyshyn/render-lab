#pragma once

#include "singleton.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "framebuffer.hpp"

namespace Lab
{

    class CResidentEvilScene : public CScene,
                               public Utils::CSingleton<CResidentEvilScene>
    {
    public:
        friend Utils::CSingleton<CResidentEvilScene>;

        void SetupScene();

        void OnUpdate(float deltaTime, CCamera &camera, CWindow &window) override;

        const std::vector<CModel> &GetSceneModels() const override { return m_Models; }

    private:
        std::vector<CModel> m_Models;
        // CModel m_DiningRoomModel;
        CShader m_DiningRoomShader;
        CFramebuffer m_Framebuffer;
        int32_t m_GuizmoOperation;

        CResidentEvilScene();
    };

} // namespace Lab
