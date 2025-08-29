#pragma once

#include "renderer/model.hpp"

namespace Lab
{
    // Forward declaration
    class CModel;
    class CShader;

    /**
     * @brief Implementation of a base class "scene entity"
     *
     * Provides common interface for all entities in a scene
     */
    class CSceneEntity
    {
    public:
        explicit CSceneEntity(const CModel &ct_Model);

        virtual ~CSceneEntity() = default;

        /**
         * @brief Draws a scene entity
         *
         * @param[in] ct_Shader Shader
         */
        virtual void Draw(CShader &ct_Shader) const;

    private:
        CModel m_Model;
    };

} // namespace Lab
