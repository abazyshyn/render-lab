#if !defined(GROUND_HPP)
#define GROUND_HPP

#include "scenes/scene_entity.hpp"

namespace Lab
{

    /**
     * Implementation of the Ground Entity
     */
    class CGround final : public CSceneEntity
    {
    public:
        explicit CGround(const CModel &ct_Model);
    };

} // namespace Lab

#endif // GROUND_HPP