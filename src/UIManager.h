#pragma once

class UIManager
{

public:

    UIManager();
    ~UIManager();

    void update();

    // Keyboard
    void keyEvent(int key, int action, int modifiers);
    bool isKeyDown(int key) const;
    bool isShiftDown() const;
    bool isControlDown() const;
    bool isAltDown() const;
    bool isModifierDown() const;

    // Mouse
    void mouseEvent(int button, int action, int modifiers);
    void mouseMove(int x, int y);
    int getMouseMoveX() const;
    int getMouseMoveY() const;
    bool isMouseMoving() const;
    bool isMouseButtonDown(int button) const;
    bool isLeftMouseButtonDown() const;
    bool isRightMouseButtonDown() const;
    bool isMiddleMouseButtonDown() const;

    // Window
    void resizeWindow(int width, int height);
    float getAspectRatio() const;

    // Time
    float getTimeSinceBeginning();
    float getFramerateAdjust();

    int m_mouseX;
    int m_mouseY;

    int m_screenWidth;
    int m_screenHeight;

    bool m_mousePressed;

    float m_frameTime;
    const float m_desiredFrameTime = 1.0f / 60.0f; // 60 FPS

protected:

    // All times are in seconds
    float m_oldFrameTime;

    int m_oldMouseX;
    int m_oldMouseY;

};
