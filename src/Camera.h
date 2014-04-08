#pragma once

#include "Entity.h"

struct CameraData;

class Camera : public Entity
{

public:

    Camera(Entity* parent, CameraData* data, const Transform& transform);
    virtual ~Camera();
    virtual void update();

    void setZoom(float amount);
    void applyZoom(float amount);

    void setPan(float x, float y);
    void applyPan(float x, float y);
    void setRotation(float x, float y);
    void applyRotation(float x, float y);

    glm::mat4 getViewMatrix();

    float m_fov; // degrees

private:

    const float m_rotationSpeed = 1.0f;
    const float m_panSpeed = 0.5f;
    const float m_zoomSpeed = 0.5f;
    const float m_smoothing = 3.0f; // 1.0 means no smoothing

    float m_angleHorizontal;
    float m_angleVertical;

    float m_rotationOldAverageX;
    float m_rotationOldAverageY;
    float m_panOldAverageX;
    float m_panOldAverageY;
    float m_zoomOldAverage;

    bool m_disabled;

};

struct CameraData : public EntityData
{
    CameraData(float fov);
    virtual ~CameraData();
    float m_fov;
};