#if !defined(LIGHTING_SPHERE_HPP)
#define LIGHTING_SPHERE_HPP

#include "scene/entities/scene_entity.hpp"

namespace Lab
{

    /**
     * @brief Implementation of the Lighting sphere
     */
    class CLightingSphere final : public CSceneEntity
    {
    public:
        explicit CLightingSphere();
    };

} // namespace Lab

#endif // LIGHTING_SPHERE_HPP
