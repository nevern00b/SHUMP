#include "UIManager.h"

#include <stdio.h>
#include "Common.h"
#include "Globals.h"
#include "Rendering/RenderManager.h"

UIManager::UIManager(float time, uint width, uint height) :
    m_oldMouseX(0),
    m_oldMouseY(0),
    m_mouseX(0),
    m_mouseY(0),
    m_screenWidth(width),
    m_screenHeight(height),
    m_oldFrameTime(time)
{

}

UIManager::~UIManager()
{

}

void UIManager::update(float time)
{
	float currTime = time;
    m_frameTime = currTime - m_oldFrameTime;
    m_oldFrameTime = currTime;
    m_oldMouseX = m_mouseX;
    m_oldMouseY = m_mouseY;
    m_mousePressed = false;
	m_keyPressed = 0;
}

void UIManager::keyEvent(int key, int action, int modifiers)
{
	#if defined(OS_WINDOWS)
	if (action == GLFW_PRESS)
	{
		m_keyPressed = key;
	}
	#endif
}

bool UIManager::isKeyPressed(int key) const
{
	return m_keyPressed == key;
}

bool UIManager::isKeyDown(int key) const
{
	#if defined(OS_WINDOWS)
		return glfwGetKey(glfwGetCurrentContext(), key) == GLFW_PRESS;
	#elif defined(OS_IOS)
		return false;
	#endif
}

bool UIManager::isShiftDown() const
{
	#if defined(OS_WINDOWS)
		return isKeyDown(GLFW_MOD_SHIFT);
	#elif defined(OS_IOS)
		return false;
	#endif
}

bool UIManager::isControlDown() const
{
	#if defined(OS_WINDOWS)
		return isKeyDown(GLFW_MOD_CONTROL);
	#elif defined(OS_IOS)
		return false;
	#endif
}

bool UIManager::isAltDown() const
{
	#if defined(OS_WINDOWS)
		return isKeyDown(GLFW_MOD_ALT);
	#elif defined(OS_IOS)
		return false;
	#endif
}

bool UIManager::isModifierDown() const
{
    return isShiftDown() || isControlDown() || isAltDown();
}

void UIManager::mouseEvent(int button, int action, int modifiers)
{
	#if defined(OS_WINDOWS)
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			m_mousePressed = true;
		}
	#endif
    
}

void UIManager::mouseMove(int x, int y)
{
    m_oldMouseX = m_mouseX;
    m_oldMouseY = m_mouseY;
    m_mouseX = x;
    m_mouseY = m_screenHeight - y;
}

int UIManager::getMouseMoveX() const
{
    return m_mouseX - m_oldMouseX;
}

int UIManager::getMouseMoveY() const
{
    return m_mouseY - m_oldMouseY;
}

bool UIManager::isMouseMoving() const
{
    return getMouseMoveX() != 0 || getMouseMoveY() != 0;
}

bool UIManager::isMouseButtonDown(int button) const
{
	#if defined(OS_WINDOWS)
		return glfwGetMouseButton(glfwGetCurrentContext(), button) == GLFW_PRESS;
	#elif defined(OS_IOS)
		return false;
	#endif
}

bool UIManager::isLeftMouseButtonDown() const
{
	#if defined(OS_WINDOWS)
		return isMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT);
	#elif defined(OS_IOS)
		return false;
	#endif
    
}

bool UIManager::isRightMouseButtonDown() const
{
	#if defined(OS_WINDOWS)
		return isMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT);
	#elif defined(OS_IOS)
		return false;
	#endif
}

bool UIManager::isMiddleMouseButtonDown() const
{
	#if defined(OS_WINDOWS)
		return isMouseButtonDown(GLFW_MOUSE_BUTTON_MIDDLE);
	#elif defined(OS_IOS)
		return false;
	#endif
}

void UIManager::resizeWindow(int width, int height)
{
    m_screenWidth = width;
    m_screenHeight = height;
	Globals::m_renderManager->resizeWindow(width, height);
}

float UIManager::getAspectRatio() const
{
    return (float)m_screenWidth / (float)m_screenHeight;
}

float UIManager::getTime()
{
	#if defined(OS_WINDOWS)
		return (float)glfwGetTime();
	#elif defined(OS_IOS)
		return m_oldFrameTime;
	#endif
}

float UIManager::getFramerateAdjust(float value)
{
    return value * (m_frameTime / m_desiredFrameTime);
}