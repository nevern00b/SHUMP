#include "Camera.h"

#include "Globals.h"
#include "Game/ShmupGame.h"
#include "UIManager.h"
#include "DataManager.h"

Camera::Camera(Entity* parent, float fov) : Entity(parent),
    m_fov(fov),
    m_angleHorizontal(0.0f),
    m_angleVertical(0.0f),
    m_rotationOldAverageX(0.0f),
    m_rotationOldAverageY(0.0f),
    m_panOldAverageX(0.0f),
    m_panOldAverageY(0.0f),
    m_zoomOldAverage(0.0f),
    m_disabled(true)
{
    // Convert transformation matrix to euler angles
    glm::mat4 rotation = glm::mat4_cast(m_transform->m_rotation);
    float eulerY = glm::atan(-rotation[1][2], rotation[1][1]);
    float eulerX = -glm::atan(rotation[2][0], rotation[0][0]);
    setRotation(eulerX, eulerY);

    Globals::m_shmupGame->setCamera(this);
}

Camera::~Camera()
{

}

bool Camera::update()
{
    if (m_disabled)
    {
        Entity::update();
        return false;
    }

	if (!Entity::update()) return false;

	UIManager* ui = Globals::m_uiManager;
    float newRotationX = 0.0f;
    float newRotationY = 0.0f;
    float newPanX = 0.0f;
    float newPanY = 0.0f;
    float newZoom = 0.0f;

    // Collect values
    if (Globals::m_uiManager->isKeyDown(GLFW_KEY_A))
    {
        newPanX = m_panSpeed;
    }
    else if (Globals::m_uiManager->isKeyDown(GLFW_KEY_D)) // D
    {
        newPanX = -m_panSpeed;
    }
    else if (Globals::m_uiManager->isKeyDown(GLFW_KEY_W)) // W
    {
        newZoom = m_panSpeed;
    }
    else if (Globals::m_uiManager->isKeyDown(GLFW_KEY_S)) // S
    {
        newZoom = -m_panSpeed;
    }

    if (Globals::m_uiManager->isMouseMoving() && Globals::m_uiManager->isLeftMouseButtonDown())
    {
        newRotationX = (float)-Globals::m_uiManager->getMouseMoveX();
        newRotationY = (float)Globals::m_uiManager->getMouseMoveY();
    }

    // Do smoothing
    m_rotationOldAverageX = ((m_smoothing - 1) * m_rotationOldAverageX + newRotationX) / m_smoothing;
    m_rotationOldAverageY = ((m_smoothing - 1) * m_rotationOldAverageY + newRotationY) / m_smoothing;
    m_panOldAverageX = ((m_smoothing - 1) * m_panOldAverageX + newPanX) / m_smoothing;
    m_panOldAverageY = ((m_smoothing - 1) * m_panOldAverageY + newPanY) / m_smoothing;
    m_zoomOldAverage = ((m_smoothing - 1) * m_zoomOldAverage + newZoom) / m_smoothing;

    // Only do camera motion if the average is non-zero
    float minAmount = 0.01f;
    if (glm::abs(m_rotationOldAverageX) > minAmount || glm::abs(m_rotationOldAverageY) > minAmount)
    {
        float speedX = m_rotationSpeed * m_rotationOldAverageX;
        float speedY = m_rotationSpeed * m_rotationOldAverageY;
        applyRotation(speedX, speedY);
    }
    if (glm::abs(m_panOldAverageX) > minAmount || glm::abs(m_panOldAverageY) > minAmount)
    {
        float speedX = -m_panSpeed * m_panOldAverageX;
        float speedY = -m_panSpeed * m_panOldAverageY;
        applyPan(ui->getFramerateAdjust(speedX), ui->getFramerateAdjust(speedY));
    }
    if (glm::abs(m_zoomOldAverage) > minAmount)
    {
        float speed = -m_zoomSpeed * m_zoomOldAverage;
        applyZoom(ui->getFramerateAdjust(speed));
    }

	return true;
}

void Camera::setZoom(float amount)
{
    glm::vec3 zoomVector = m_transform->getForwardVector();
    zoomVector *= amount;
    m_transform->setTranslation(zoomVector);
}

void Camera::applyZoom(float amount)
{
    glm::vec3 zoomVector = m_transform->getForwardVector();
    zoomVector *= amount;
    m_transform->translate(zoomVector);
}

void Camera::setPan(float x, float y)
{
    glm::vec3 rightVector = m_transform->getRightVector();
    rightVector *= x;
    glm::vec3 upVector = m_transform->getUpVector();
    upVector *= y;
    glm::vec3 panVector = rightVector + upVector;
    m_transform->setTranslation(panVector);
}

void Camera::applyPan(float x, float y)
{
    glm::vec3 rightVector = m_transform->getRightVector();
    rightVector *= x;
    glm::vec3 upVector = m_transform->getUpVector();
    upVector *= y;
    glm::vec3 panVector = rightVector + upVector;
    m_transform->translate(panVector);
}

void Camera::setRotation(float x, float y)
{
    m_angleHorizontal = x;
    m_angleVertical = y;

    glm::quat rotation;
    rotation = glm::rotate(rotation, glm::radians(m_angleHorizontal), glm::vec3(0, 1, 0));
    rotation = glm::rotate(rotation, glm::radians(m_angleVertical), glm::vec3(1, 0, 0));

    m_transform->setRotation(rotation);
}

void Camera::applyRotation(float x, float y)
{
    setRotation(m_angleHorizontal + x, m_angleVertical + y);
}

glm::mat4 Camera::getViewMatrix()
{
    glm::mat4 viewMatrix = m_renderMatrix;
    viewMatrix = glm::inverse(viewMatrix);
    return viewMatrix;
}
