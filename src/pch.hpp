#pragma once

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
#include <string.h>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#if defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)

#include "log.hpp"
#include "assert.hpp"

// #include <gtest/gtest.h>

#endif // defined(LAB_DEBUG) || defined(LAB_DEVELOPMENT)
