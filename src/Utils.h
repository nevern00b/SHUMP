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

class Timer
{
public:
	Timer();
	~Timer();
	void start();
	void stop();
	float getTimeElapsed();

private:
	float m_timeElapsed;
	float m_startTime;
};