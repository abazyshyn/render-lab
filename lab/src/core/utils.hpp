#if !defined(UTILS_HPP)
#define UTILS_HPP

#include "assert.hpp"
#include <type_traits>

namespace Utils
{

    /**
     * @brief Base path to shaders
     */
    const std::string LAB_BASE_SHADERS_PATH = "../../../../lab/res/shaders/";

    /**
     * @brief Base path to models
     */
    const std::string LAB_BASE_MODELS_PATH = "../../../../lab/res/models/";

    // TODO: docs
    template <typename T>
    class CSingleton
    {
    public:
        // TODO: docs
        static T &GetInstance()
        {
            LAB_ASSERT(std::is_base_of(CSingleton, T));

            static T instance;
            return instance;
        }

        virtual ~CSingleton() = default;

    protected:
        CSingleton() = default;
        CSingleton(const CSingleton &ct_Source) = delete;
        CSingleton(CSingleton &&t_Source) = delete;

        CSingleton &operator=(const CSingleton &ct_RHV) = delete;
        CSingleton &operator=(CSingleton &&t_RHV) = delete;
    };

} // namespace Utils

#endif // UTILS_HPP
