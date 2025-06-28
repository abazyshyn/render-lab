#if !defined(PCH_HPP)
#define PCH_HPP

#include <memory>
#include <chrono>
#include <utility>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <functional>

#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "core/core.hpp"
// Debug
#include "core/log.hpp"
#include "core/assert.hpp"
// #if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)
//
// #include <gtest/gtest.h>
//
// #endif

#endif // _LAB_PCH_HPP_
