#if !defined(GROUND_HPP)
#define GROUND_HPP

#include "scene_entity/scene_entity.hpp"

namespace Lab
{

    /**
     * Implementation of the Ground Entity
     */
    class CGround final : public CSceneEntity
    {
    public:
        CGround(const CModel &ct_Model);
    };

} // namespace Lab

#endif // GROUND_HPP