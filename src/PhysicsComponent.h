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
    PhysicsComponent(Entity* entity, const PhysicsData& physicsData);
    virtual ~PhysicsComponent();

    virtual void update();
    virtual void setRotation(const glm::quat& quat);
    virtual void setTranslation(const glm::vec3& translation);

    b2Body* m_body;
};



struct PhysicsData
{
	PhysicsData(b2Shape* shape, float x, float y);

    b2Shape* m_shape;
    
    b2BodyType m_bodyType;
    uint m_categoryBits;
    uint m_maskBits;
    uint m_groupIndex;
    float m_vx;
    float m_vy;
	float m_x;
	float m_y;
};