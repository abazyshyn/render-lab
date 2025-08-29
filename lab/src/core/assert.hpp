#pragma once

#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)

#include "log.hpp"

#if defined(LAB_LINUX)

#include <csignal>

/**
 * @brief Macro for braking on a line where assertion fails
 */
#define DEBUG_BREAK raise(SIGTRAP)

#elif defined(LAB_WINDOWS) // LAB_LINUX

/**
 * @brief Macro for braking on a line where assertion fails
 */
#define DEBUG_BREAK __debugbreak()

#else // LAB_WINDOWS, LAB_LINUX

#error RenderLab supports only Linux and Windows.

#endif // LAB_WINDOWS, LAB_LINUX

/**
 * @brief Custom assertion macro
 *
 * @param[in] expr Boolean expression
 */
#define LAB_ASSERT(expr)                                      \
    if (!expr)                                                \
    {                                                         \
        Lab::Log(Lab::LAB_LOG_MESSAGE_SEVERITY_ERROR,         \
                 "[LAB_ASSERT]: Assertion failed\n",          \
                 "\rExpression:", #expr, "\nFile:", __FILE__, \
                 "\nLine:", __LINE__);                        \
        DEBUG_BREAK;                                          \
    }

#else // defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)

/**
 * @brief Macro that evaluates to nothing
 */
#define DEBUG_BREAK

/**
 * @brief Macro that evaluates to nothing
 */
#define LAB_ASSERT(expr)

#endif // defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)
