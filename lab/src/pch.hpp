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

#include <map>
#include <array>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "core/utils.hpp"

#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)

#include "core/log.hpp"
#include "core/assert.hpp"

// #include <gtest/gtest.h>

#endif // defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)

#endif // PCH_HPP
