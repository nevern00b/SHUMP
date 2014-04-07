#pragma once

#include <glm/glm.hpp>
#include "Entity.h"

struct LightData;

class Light : public Entity
{
public:
    Light(Entity* parent, LightData* lightData, const Transform& transform);
    virtual ~Light();

    glm::vec3 m_color;
};

class DirLight : public Light
{
public:
    DirLight(Entity* parent, LightData* data, const Transform& transform);
    virtual ~DirLight();
    glm::vec3 getDirection();
};

class PointLight : public Light
{
public:
    PointLight(Entity* parent, LightData* data, const Transform& transform);
    virtual ~PointLight();

    float m_radius;
};

struct LightData : public EntityData
{
    LightData(const glm::vec3& color, float radius);
    virtual ~LightData();
    glm::vec3 m_color;
    float m_radius;
};