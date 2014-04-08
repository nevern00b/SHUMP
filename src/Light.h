#pragma once

#include <glm/glm.hpp>
#include "Entity.h"

struct LightData;

class Light : public Entity
{
public:
    Light(Entity* parent, const glm::vec3& color);
    virtual ~Light();

    glm::vec3 m_color;
};

class DirLight : public Light
{
public:
    DirLight(Entity* parent, const glm::vec3& color);
    virtual ~DirLight();
    glm::vec3 getDirection();
};

class PointLight : public Light
{
public:
    PointLight(Entity* parent, const glm::vec3& color, float radius);
    virtual ~PointLight();

    float m_radius;
};