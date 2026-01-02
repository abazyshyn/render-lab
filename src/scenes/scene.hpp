#pragma once

#include "camera.hpp"
#include "window.hpp"
#include "model.hpp"

namespace Lab
{

    class CScene
    {
    public:
        virtual ~CScene() = default;

        virtual void OnUpdate(float deltaTime, CCamera &camera, CWindow &window) = 0;

        virtual std::vector<CModel> &GetSceneModels() = 0;
    };

} // namespace Lab
