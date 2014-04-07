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

    glm::vec2 parseVec2(const std::string& vecString);
    glm::vec3 parseVec3(const std::string& vecString);
    glm::vec4 parseVec4(const std::string& vecString);
    glm::quat parseQuat(const std::string& quatString);
    glm::mat4 parseMat4(const std::string& matrixString);
    std::vector<std::string> parseSpaceSeparatedString(const std::string& data);
    std::vector<glm::vec3> parseVec3s(const std::string& data, uint count);
    std::vector<float> parseFloats(const std::string& data, uint count);
    std::vector<glm::quat> parseQuats(const std::string& data, uint count);

    std::string loadFile(const std::string& filename);
    std::string getNameFromFilename(const std::string& filename);

    Ray getPickingRay();
}

struct Ray
{
    Ray(const glm::vec3& position, const glm::vec3& direction);
    glm::vec3 m_position;
    glm::vec3 m_direction;
};