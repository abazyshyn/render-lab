#include "pch.hpp"

#include "renderer/model.hpp"

#include "scene_entity.hpp"

namespace Lab
{

    CSceneEntity::CSceneEntity(const CModel &ct_Model)
        : m_Model(ct_Model)
    {
    }

} // namespace Lab