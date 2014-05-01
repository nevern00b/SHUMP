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
	m_mouseDown = false;
	m_keyPressed = 0;
}

void UIManager::keyPressEvent(int key)
{
	m_keyPressed = key;
}

bool UIManager::isKeyDown(int key) const
{
	#if defined(OS_WINDOWS)
		return glfwGetKey(glfwGetCurrentContext(), key) == GLFW_PRESS;
	#elif defined(OS_IOS)
		return false;
	#endif
}

bool UIManager::isKeyPressed(int key) const
{
	return m_keyPressed == key;
}

void UIManager::mouseMoveEvent(int x, int y)
{
	m_oldMouseX = m_mouseX;
	m_oldMouseY = m_mouseY;
	m_mouseX = x;
	m_mouseY = m_screenHeight - y;
}

void UIManager::mousePressEvent()
{
	m_mousePressed = true;
}

void UIManager::mouseDownEvent()
{
	m_mouseDown = true;
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

bool UIManager::isMouseDragging() const
{
	return m_mouseDown && isMouseMoving() && !m_mousePressed;
}

void UIManager::resizeWindowEvent(int width, int height)
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