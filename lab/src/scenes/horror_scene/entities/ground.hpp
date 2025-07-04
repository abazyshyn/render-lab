#if !defined(GROUND_HPP)
#define GROUND_HPP

#include "scenes/scene_entity.hpp"

namespace Lab
{

    /**
     * @brief Implementation of the Ground Entity
     */
    class CGround final : public CSceneEntity
    {
    public:
        // TODO: provide model construction directly in this class
        explicit CGround(const CModel &ct_Model);
    };

} // namespace Lab

#endif // GROUND_HPP
