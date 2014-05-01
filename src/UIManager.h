#pragma once

#include <vector>
#include "Common.h"

class UIManager
{

public:

    UIManager(float time, uint width, uint height);
    ~UIManager();

    void update(float time);

    // Keyboard
    void keyPressEvent(int key);
    bool isKeyDown(int key) const;
	bool isKeyPressed(int key) const;

    // Mouse
    void mouseMoveEvent(int x, int y);
	void mousePressEvent();
	void mouseDownEvent();
	int getMouseMoveX() const;
    int getMouseMoveY() const;
    bool isMouseMoving() const;
	bool isMouseDragging() const;

    // Window
    void resizeWindowEvent(int width, int height);
    float getAspectRatio() const;

    // Time
    float getTime();
    float getFramerateAdjust(float value);

    int m_mouseX;
    int m_mouseY;

	int m_oldMouseX;
	int m_oldMouseY;

    int m_screenWidth;
    int m_screenHeight;

    bool m_mousePressed;
	bool m_mouseDown;

    float m_frameTime;
	
    const float m_desiredFrameTime = 1.0f / 60.0f; // 60 FPS

protected:

    // All times are in seconds
    float m_oldFrameTime;

	int m_keyPressed;
};

#define KEY_A                  65
#define KEY_B                  66
#define KEY_C                  67
#define KEY_D                  68
#define KEY_E                  69
#define KEY_F                  70
#define KEY_G                  71
#define KEY_H                  72
#define KEY_I                  73
#define KEY_J                  74
#define KEY_K                  75
#define KEY_L                  76
#define KEY_M                  77
#define KEY_N                  78
#define KEY_O                  79
#define KEY_P                  80
#define KEY_Q                  81
#define KEY_R                  82
#define KEY_S                  83
#define KEY_T                  84
#define KEY_U                  85
#define KEY_V                  86
#define KEY_W                  87
#define KEY_X                  88
#define KEY_Y                  89
#define KEY_Z                  90