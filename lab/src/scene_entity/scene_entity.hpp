#if !defined(SCENE_ENTITY_HPP)
#define SCENE_ENTITY_HPP

namespace Lab
{

    /**
     * @brief Implementation of a base class Scene Entity
     *
     * Provides common interface for all Entities in a scene
     */
    class CSceneEntity
    {
    public:
        /**
         * Entity model
         */
        CModel m_Model; // TODO: make a private

        CSceneEntity(const CModel &ct_Model);

        virtual ~CSceneEntity() = default;
    };

} // namespace Lab

#endif // SCENE_ENTITY_HPP