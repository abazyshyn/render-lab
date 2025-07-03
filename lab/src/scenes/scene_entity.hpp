#if !defined(SCENE_ENTITY_HPP)
#define SCENE_ENTITY_HPP

namespace Lab
{

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
        virtual void Draw(const CShader &ct_Shader) const;

    private:
        std::unique_ptr<CModel> m_Model;
    };

} // namespace Lab

#endif // SCENE_ENTITY_HPP
