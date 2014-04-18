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
	uint getLevels(uint textureSize);
}

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