#pragma once

#include "assert.hpp"
#include <type_traits>

namespace Utils
{

    /**
     * @brief Base path to shaders
     */
    const std::string LAB_BASE_SHADERS_PATH = LAB_RES_DIR "/shaders/";

    /**
     * @brief Base path to models
     */
    const std::string LAB_BASE_MODELS_PATH = LAB_RES_DIR "/models/";

    /**
     * @brief Implementation of the "base singleton class"
     *
     * Implemented using Mayers' Singleton pattern
     *
     * Neither CopyConstructible/MoveConstructible nor
     * CopyAssignable/MoveAssignable
     */
    template <typename T>
    class CSingleton
    {
    public:
        /**
         * @brief Returns the only one existing instance of type T
         *
         * @return Instance
         */
        static T &GetInstance()
        {
            const bool expr = std::is_base_of<CSingleton, T>::value;

            LAB_ASSERT(expr);

            static T instance;
            return instance;
        }

        CSingleton(const CSingleton &ct_Source) = delete;
        CSingleton(CSingleton &&t_Source) = delete;

        CSingleton &operator=(const CSingleton &ct_RHV) = delete;
        CSingleton &operator=(CSingleton &&t_RHV) = delete;

        virtual ~CSingleton() = default;

    protected:
        CSingleton() = default;
    };

} // namespace Utils
