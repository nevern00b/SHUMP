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
    
    extern std::string m_directory;
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