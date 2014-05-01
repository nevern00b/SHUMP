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
    std::string formatPath(const std::string& filename);
    void setDirectory(const std::string& directory);
	uint getLevels(uint textureSize);

	Ray getPickingRay();
	Ray getPickingRay(uint mouseX, uint mouseY);

    extern std::string m_directory;
}

struct Ray
{
	Ray(const glm::vec3& position, const glm::vec3& direction);
	glm::vec3 m_position;
	glm::vec3 m_direction;
};

class Timer
{
public:
	Timer(float interval);
	~Timer();
	void start();
	float getTimeElapsed();
	void setInterval(float interval);
	bool checkInterval();

private:
	float m_startTime;
	float m_interval;
};