#pragma once

#include <Box2D/Collision/Shapes/b2Shape.h>
#include <Box2D/Dynamics/b2Body.h>
#include "Common.h"
#include "Transform.h"

class Entity;
struct PhysicsData;

class PhysicsComponent : public Transform
{
public:
    PhysicsComponent(Entity* entity, PhysicsData* physicsData, const Transform& transform);
    ~PhysicsComponent();

    virtual void update();
    virtual void setRotation(const glm::quat& quat);
    virtual void setTranslation(const glm::vec3& translation);
    virtual void setScale(const glm::vec3& scale);

    b2Body* m_body;
};



struct PhysicsData
{
    PhysicsData(b2Shape* shape, float density, float friction, float restitution);
    ~PhysicsData();

    b2Shape* m_shape;
    float m_density;
    float m_friction;
    float m_restitution;

    b2BodyType m_bodyType;
    bool m_isSensor;
    uint m_categoryBits;
    uint m_maskBits;
    uint m_groupIndex;
    float m_vx;
    float m_vy;
};