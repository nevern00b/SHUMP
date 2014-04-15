#include "UIManager.h"

#include <stdio.h>
#include "Common.h"

UIManager::UIManager() : 
    m_oldMouseX(0),
    m_oldMouseY(0),
    m_mouseX(0),
    m_mouseY(0),
    m_screenWidth(0),
    m_screenHeight(0),
    m_oldFrameTime(0.0)
{

}

UIManager::~UIManager()
{

}

void UIManager::update()
{
    float currTime = (float)glfwGetTime();
    m_frameTime = currTime - m_oldFrameTime;
    m_oldFrameTime = currTime;
    m_oldMouseX = m_mouseX;
    m_oldMouseY = m_mouseY;
    m_mousePressed = false;
	m_keyPressed = 0;
}

void UIManager::keyEvent(int key, int action, int modifiers)
{
	if (action == GLFW_PRESS)
	{
		//if (!isKeyDown(key))
		//{
			m_keyPressed = key;
		//}
	}
}

bool UIManager::isKeyPressed(int key) const
{
	return m_keyPressed == key;
}

bool UIManager::isKeyDown(int key) const
{
    return glfwGetKey(glfwGetCurrentContext(), key) == GLFW_PRESS;
}

bool UIManager::isShiftDown() const
{
    return isKeyDown(GLFW_MOD_SHIFT);
}

bool UIManager::isControlDown() const
{
    return isKeyDown(GLFW_MOD_CONTROL);
}

bool UIManager::isAltDown() const
{
    return isKeyDown(GLFW_MOD_ALT);
}

bool UIManager::isModifierDown() const
{
    return isShiftDown() || isControlDown() || isAltDown();
}

void UIManager::mouseEvent(int button, int action, int modifiers)
{
    //broadcastMessage(MESSAGE_LOCATION::GLOBAL, MouseEventMessage(button, action, modifiers));
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        m_mousePressed = true;
    }
}

void UIManager::mouseMove(int x, int y)
{
    m_oldMouseX = m_mouseX;
    m_oldMouseY = m_mouseY;
    m_mouseX = x;
    m_mouseY = m_screenHeight - y;
    //broadcastMessage(MESSAGE_LOCATION::GLOBAL, MouseMoveMessage());
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
    return glfwGetMouseButton(glfwGetCurrentContext(), button) == GLFW_PRESS;
}

bool UIManager::isLeftMouseButtonDown() const
{
    return isMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT);
}

bool UIManager::isRightMouseButtonDown() const
{
    return isMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT);
}

bool UIManager::isMiddleMouseButtonDown() const
{
    return isMouseButtonDown(GLFW_MOUSE_BUTTON_MIDDLE);
}

void UIManager::resizeWindow(int width, int height)
{
    m_screenWidth = width;
    m_screenHeight = height;
    //broadcastMessage(MESSAGE_LOCATION::GLOBAL, ResizeWindowMessage());
}

float UIManager::getAspectRatio() const
{
    return (float)m_screenWidth / (float)m_screenHeight;
}

float UIManager::getTimeSinceBeginning()
{
    return (float)glfwGetTime();
}

float UIManager::getFramerateAdjust(float value)
{
    return value * (m_frameTime / m_desiredFrameTime);
}