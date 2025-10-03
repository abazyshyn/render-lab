#pragma once

#include <stdexcept>
#include <sstream>
#include <type_traits>

namespace Utils
{

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

            if constexpr (!expr)
            {
                std::stringstream ss;
                ss << "Provided type \"" << typeid(T).name() << "\" is not derived from the base CSingleton";
                throw std::runtime_error(ss.str());
            }

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
