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
	Timer();
	~Timer();
	void start(float interval, bool repeat);
	void stop();
	float getTimeElapsed();
	float getTimeLeft();
	bool checkInterval();

	float m_interval;
	bool m_running;

private:
	float m_startTime;
	bool m_repeat;
	
};