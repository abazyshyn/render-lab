#if !defined(ASSERT_HPP)
#define ASSERT_HPP

#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)

#include "log.hpp"

#if defined(LAB_LINUX)

#include <csignal>

#define DEBUG_BREAK raise(SIGTRAP)

#elif defined(LAB_WINDOWS)

#define DEBUG_BREAK __debugbreak()

#else

#error RenderLab supports only Linux and Windows.

#endif

/**
 * @brief Custom assertion macro
 *
 * @param expr Boolean expression
 */
#define LAB_ASSERT(expr)                                      \
    if (!expr)                                                \
    {                                                         \
        Lab::Log(LAB_LOG_MESSAGE_SEVERITY_ERROR,              \
                 "[LAB_ASSERT]: Assertion failed\n",          \
                 "\rExpression:", #expr, "\nFile:", __FILE__, \
                 "\nLine:", __LINE__);                        \
        DEBUG_BREAK;                                          \
    }

#else

#define DEBUG_BREAK
#define LAB_ASSERT(expr)

#endif

#endif // ASSERT_HPP
