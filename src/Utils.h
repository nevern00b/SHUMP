#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Common.h"

struct Ray;

namespace Utils
{
    bool checkBitfield(uint renderStateBitfield, uint renderStateEnum);
    std::string loadFile(const std::string& filename);
}
