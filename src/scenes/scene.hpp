#pragma once

#include "camera.hpp"
#include "window.hpp"
#include "model.hpp"

namespace Lab
{

    class CScene
    {
    public:
        friend Utils::CSingleton<CScene>;

        virtual ~CScene() = default;

        // void SetupScene();

        virtual void OnUpdate(float deltaTime, CCamera &camera, CWindow &window);

        virtual const std::vector<CModel> &GetSceneModels() const;
    };

} // namespace Lab
