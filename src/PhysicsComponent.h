#pragma once

//#include <Box2D/Collision/Shapes/b2Shape.h>
//#include <Box2D/Dynamics/b2Body.h>
//#include "Common.h"
//#include "Transform.h"
//
//class PhysicsComponent : public Transform
//{
//public:
//    PhysicsComponent(Entity* entity, PhysicsData* physicsData, const Transform& transform);
//    ~PhysicsComponent();
//
//    virtual void setRotation(const glm::quat& quat);
//    virtual void setTranslation(const glm::vec3& translation);
//    virtual void setScale(const glm::vec3& scale);
//    virtual glm::mat4 getMatrix() const;
//
//    b2Body* m_body;
//
//private:
//    b2Shape* m_shape;
//};
//
//struct PhysicsData
//{
//    PhysicsData();
//    PhysicsData(float mass, float friction, float restitution, b2Shape* shape);
//    ~PhysicsData();
//
//    b2Shape* m_shape;
//    float m_mass;
//    float m_friction;
//    float m_restitution;
//};