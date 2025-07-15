#include "pch.hpp"

#include "sponza.hpp" // target

namespace Lab
{

    CSponza::CSponza()
        : CSceneEntity(CModel(Utils::LAB_BASE_MODELS_PATH + "sponza/scene.gltf"))
    {
    }

} // namespace Lab
