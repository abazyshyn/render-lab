#include "pch.hpp"

#include "scene_entity.hpp" // target

#include "renderer/shader.hpp"

namespace Lab
{

    CSceneEntity::CSceneEntity(const CModel &ct_Model)
        : m_Model(ct_Model)
    {
    }

    void CSceneEntity::Draw(CShader &ct_Shader) const
    {
        m_Model.Draw(ct_Shader);
    }

} // namespace Lab
