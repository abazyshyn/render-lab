#include "pch.hpp"

#include "log.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Lab
{

    std::shared_ptr<spdlog::logger> CLog::s_LabLogger;

    void CLog::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        s_LabLogger = spdlog::stdout_color_mt("LAB");
        s_LabLogger->set_level(spdlog::level::level_enum::trace);
    }

} // namespace Lab
