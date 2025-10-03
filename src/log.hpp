#pragma once

#include "singleton.hpp"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Lab
{

    /**
     * @brief Implementation of the logging system
     *
     * Implemented using Mayers' Singleton pattern
     *
     * Neither CopyConstructible/MoveConstructible nor
     * CopyAssignable/MoveAssignable
     */
    class CLog final : public Utils::CSingleton<CLog>
    {
    public:
        friend Utils::CSingleton<CLog>;

        /**
         * @brief Initializes loggers for the engine and client side
         */
        static void Init();

        /**
         * @brief Returns engine logger
         *
         * @return Lab logger
         */
        inline static std::shared_ptr<spdlog::logger> &GetLabLogger() { return s_LabLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_LabLogger;
    };

} // namespace Lab

// TODO: Consider creation of macro for displaying info even in SHIP mode
#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)

#define LAB_TRACE_LOG(...) ::Lab::CLog::GetLabLogger()->trace(__VA_ARGS__)
#define LAB_INFO_LOG(...) ::Lab::CLog::GetLabLogger()->info(__VA_ARGS__)
#define LAB_WARN_LOG(...) ::Lab::CLog::GetLabLogger()->warn(__VA_ARGS__)
#define LAB_ERROR_LOG(...) ::Lab::CLog::GetLabLogger()->error(__VA_ARGS__)
#define LAB_CRITICAL_LOG(...) ::Lab::CLog::GetLabLogger()->critical(__VA_ARGS__)

#else // defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)

#define LAB_TRACE_LOG(...)
#define LAB_INFO_LOG(...)
#define LAB_WARN_LOG(...)
#define LAB_ERROR_LOG(...)
#define LAB_CRITICAL_LOG(...)

#endif // defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)
