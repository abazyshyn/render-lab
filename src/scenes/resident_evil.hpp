#pragma once

#include <singleton.hpp>
#include <model.hpp>
#include <shader.hpp>
#include "camera.hpp"
#include "window.hpp"

namespace Lab
{

    class CResidentEvilScene : public Utils::CSingleton<CResidentEvilScene>
    {
    public:
        friend Utils::CSingleton<CResidentEvilScene>;

        void SetupScene();

        void OnUpdate(float deltaTime, CCamera &camera, CWindow &window);

    private:
        CModel m_DiningRoomModel;
        CShader m_DiningRoomShader;

        CResidentEvilScene();
    };

} // namespace Lab
