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

	Ray getPickingRay()
	{
		uint mouseX = Globals::m_uiManager->m_mouseX;
		uint mouseY = Globals::m_uiManager->m_mouseY;
		return getPickingRay(mouseX, mouseY);
	}

	Ray getPickingRay(uint mouseX, uint mouseY)
	{
		uint screenWidth = Globals::m_uiManager->m_screenWidth;
		uint screenHeight = Globals::m_uiManager->m_screenHeight;
		glm::mat4 viewMatrix = Globals::m_renderManager->m_viewMatrix;
		glm::mat4 projMatrix = Globals::m_renderManager->m_projMatrix;

		glm::vec4 viewport(0.0f, 0.0f, screenWidth, screenHeight);
		glm::vec3 windowPosClose(mouseX, mouseY, 0.0f);
		glm::vec3 windowPosFar(mouseX, mouseY, 1.0f);

		glm::vec3 nearPlanePoint = glm::unProject(windowPosClose, viewMatrix, projMatrix, viewport);
		glm::vec3 farPlanePoint = glm::unProject(windowPosFar, viewMatrix, projMatrix, viewport);

		glm::vec3 position = nearPlanePoint;
		glm::vec3 direction = glm::normalize(farPlanePoint - nearPlanePoint);
		Ray r(position, direction);
		return r;
	}
}

Ray::Ray(const glm::vec3& position, const glm::vec3& direction) :
	m_position(position),
	m_direction(direction)
{

}


Timer::Timer() :
	m_running(false)
{

}

Timer::~Timer()
{

}

void Timer::start(float interval, bool repeat)
{
	m_interval = interval;
	m_startTime = Globals::m_uiManager->getTime();
	m_running = true;
	m_repeat = repeat;
}

void Timer::stop()
{
	m_running = false;
}

float Timer::getTimeElapsed()
{
	if (!m_running)
	{
		return 0.0f;
	}
	else
	{
		return Globals::m_uiManager->getTime() - m_startTime;
	}
}

float Timer::getTimeLeft()
{
	if (!m_running)
	{
		return 0.0f;
	}
	else
	{
		return m_startTime + m_interval - Globals::m_uiManager->getTime();
	}
}

bool Timer::checkInterval()
{
	if (getTimeElapsed() > m_interval)
	{
		if (m_repeat)
		{
			start(m_interval, m_repeat);
		}
		else
		{
			stop();
		}
		
		return true;
	}

	return false;
}

void Timer::setInterval(float interval)
{
	m_interval = interval;
}
