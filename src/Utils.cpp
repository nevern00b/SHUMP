#include "Utils.h"

#include <sstream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Globals.h"
#include "UIManager.h"
#include "GameManager.h"
#include "Rendering/RenderManager.h"
#include "Camera.h"
#include "Globals.h"
#include "UIManager.h"

namespace Utils
{
    std::string m_directory = "";
    
    bool checkBitfield(uint renderStateBitfield, uint renderStateEnum)
    {
        return (renderStateBitfield & renderStateEnum) > 0;
    }

    std::string loadFile(const std::string& filename)
    {
        std::string path = formatPath(filename);
        std::ifstream stream(path.c_str(), std::ios::in);
        return std::string(std::istreambuf_iterator<char>(stream),
            std::istreambuf_iterator<char>());
    }

    std::string formatPath(const std::string& filename)
    {
        return m_directory + filename;
    }
    
    void setDirectory(const std::string& directory)
    {
        m_directory = directory;
    }
    
	uint getLevels(uint textureSize)
	{
		uint numLevels = 1 + (uint)glm::floor(glm::log2((float)textureSize));
		return numLevels;
	}
}



Timer::Timer(float interval)
{
	setInterval(interval);
}

Timer::~Timer()
{

}

void Timer::start()
{
	m_startTime = Globals::m_uiManager->getTime();
}

float Timer::getTimeElapsed()
{
	return Globals::m_uiManager->getTime() - m_startTime;
}

void Timer::setInterval(float interval)
{
	m_interval = interval;
}

bool Timer::checkInterval()
{
	if (getTimeElapsed() > m_interval)
	{
		start();
		return true;
	}

	return false;
}
