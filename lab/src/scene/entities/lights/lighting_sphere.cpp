#include "pch.hpp"

#include "lighting_sphere.hpp" // target

#include "renderer/model.hpp"

namespace Lab
{

    CLightingSphere::CLightingSphere()
        : CSceneEntity(CModel(Utils::LAB_BASE_MODELS_PATH + "lighting_sphere/lighting_sphere.fbx"))
    {
    }

} // namespace Lab
