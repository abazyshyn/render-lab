#if !defined(I_SCENE_HPP)
#define I_SCENE_HPP

namespace Lab
{

    /**
     * @brief Implementation of the "scene interface"
     */
    class CIScene
    {
    public:
        virtual ~CIScene() = default;

        /**
         * @brief Updates a scene entities
         *
         * @param[in] t_DeltaTime Time taken to render last frame
         */
        virtual void OnUpdate(float t_DeltaTime) = 0;
    };

} // namespace Lab

#endif // I_SCENE_HPP