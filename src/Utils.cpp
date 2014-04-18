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
#include "GLFW/glfw3.h"
#include "Globals.h"
#include "UIManager.h"

namespace Utils
{
    bool checkBitfield(uint renderStateBitfield, uint renderStateEnum)
    {
        return (renderStateBitfield & renderStateEnum) > 0;
    }

    std::string loadFile(const std::string& filename)
    {
        std::ifstream stream(filename.c_str(), std::ios::in);
        return std::string(std::istreambuf_iterator<char>(stream),
            std::istreambuf_iterator<char>());
    }

	uint getLevels(uint textureSize)
	{
		uint numLevels = 1 + (uint)glm::floor(glm::log2((float)textureSize));
		return numLevels;
	}
}



Timer::Timer() :
	m_timeElapsed(0.0f)
{

}

Timer::~Timer()
{

}

void Timer::start()
{
	m_startTime = (float)glfwGetTime();
}

void Timer::stop()
{
	float currTime = (float)glfwGetTime();
	m_timeElapsed = currTime - m_startTime;
}

float Timer::getTimeElapsed()
{
	return m_timeElapsed;
}
