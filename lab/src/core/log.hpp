#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)

namespace Lab
{

    /**
     * @brief Types of message severity
     */
    enum LogMessageSeverity_e
    {
        LAB_LOG_MESSAGE_SEVERITY_TRACE = 30,
        LAB_LOG_MESSAGE_SEVERITY_ERROR = 91,
        LAB_LOG_MESSAGE_SEVERITY_WARN = 93,
        LAB_LOG_MESSAGE_SEVERITY_INFO = 94
    };

    /**
     * @brief Converts objects to a string representation
     *
     * @tparam[in] t_Object Template parameter
     * @return C++ String
     */
    template <typename T>
    std::string ToString(T &t_Object);

    /**
     * @brief Logs message to a console
     *
     * @relatesalso Log
     *
     * @param[in] ct_MessageSeverity Type of message severity
     * @param[in] ct_Message Message
     */
    inline void PrintMessage(LogMessageSeverity_e ct_MessageSeverity, const std::string &ct_Message);

    /**
     * @brief Logs message to a console
     *
     * @param[in] ct_MessageSeverity Type of message severity
     * @param[in] ct_Args Variadic arguments
     */
    template <typename... Args>
    void Log(const LogMessageSeverity_e ct_MessageSeverity, const Args &...ct_Args)
    {
        // Convert arguments to a string
        const std::vector<std::string> messages = {ToString(ct_Args)...};

        // Print all messages
        std::cout << "[RenderLab]:\n";
        for (const std::string &message : messages)
        {
            PrintMessage(ct_MessageSeverity, message);
        }

        // New line after displaying all messages
        std::cout << "\033[0m" << std::endl;
    }

    template <typename T>
    std::string ToString(T &t_Object)
    {
        std::stringstream ssParser;
        ssParser << t_Object;
        return ssParser.str();
    }

    inline void PrintMessage(const LogMessageSeverity_e ct_MessageSeverity, const std::string &ct_Message)
    {
        ct_MessageSeverity == LAB_LOG_MESSAGE_SEVERITY_TRACE
            ? std::cout << ct_Message << std::flush
            : std::cout << "\033[" << ct_MessageSeverity << "m" << ct_Message << std::flush;
    }

} // namespace Lab

/**
 * @brief Macros for logging
 */
#define LAB_TRACE_LOG(...) ::Lab::Log(Lab::LAB_LOG_MESSAGE_SEVERITY_TRACE, __VA_ARGS__)
#define LAB_INFO_LOG(...) ::Lab::Log(Lab::LAB_LOG_MESSAGE_SEVERITY_INFO, __VA_ARGS__)
#define LAB_WARN_LOG(...) ::Lab::Log(Lab::LAB_LOG_MESSAGE_SEVERITY_WARN, __VA_ARGS__)
#define LAB_ERROR_LOG(...) ::Lab::Log(Lab::LAB_LOG_MESSAGE_SEVERITY_ERROR, __VA_ARGS__)

#else // defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)

/**
 * @brief Macros that evaluates to nothing
 */
#define LAB_TRACE_LOG(...)
#define LAB_INFO_LOG(...)
#define LAB_WARN_LOG(...)
#define LAB_ERROR_LOG(...)

#endif // defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)
