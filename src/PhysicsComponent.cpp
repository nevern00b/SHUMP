#include "PhysicsComponent.h"

#include <Box2D/Box2D.h>
#include "Utils.h"
#include "Globals.h"
#include "PhysicsManager.h"
#include "Mesh.h"
#include "Entity.h"
#include "Transform.h"


PhysicsComponent::PhysicsComponent(Entity* entity, const PhysicsData& physicsData) : Transform(entity)
{
	// Replace the default Transform
    delete entity->m_transform;
    entity->m_physics = this;
    entity->m_transform = this;

    // Create the b2body
    b2BodyDef& bodyDef = Globals::m_physicsManager->m_sharedBodyDef;
	bodyDef.position = b2Vec2(physicsData.m_x, physicsData.m_y);
    bodyDef.linearVelocity = b2Vec2(physicsData.m_vx, physicsData.m_vy);
    bodyDef.type = physicsData.m_bodyType;
    bodyDef.userData = entity;
    bodyDef.fixedRotation = true;

    m_body = Globals::m_physicsManager->m_world->CreateBody(&bodyDef);

    // Create fixture and add to body
    b2FixtureDef& fixtureDef = Globals::m_physicsManager->m_sharedFixtureDef;
    fixtureDef.shape = physicsData.m_shape;
    fixtureDef.isSensor = true;
    fixtureDef.filter.categoryBits = physicsData.m_categoryBits;
    fixtureDef.filter.maskBits = physicsData.m_maskBits;
    fixtureDef.filter.groupIndex = physicsData.m_groupIndex;
	fixtureDef.userData = 0;

    m_body->CreateFixture(&fixtureDef);
}

PhysicsComponent::~PhysicsComponent()
{
    Globals::m_physicsManager->destroyPhysicsComponent(this);
}

void PhysicsComponent::update()
{
    b2Vec2 pos = m_body->GetPosition();
	float angle = m_body->GetAngle();
    
	// Rotate about the z-axis
	m_rotation = glm::angleAxis(angle, glm::vec3(0, 0, 1));
	m_translation.x = pos.x;
	m_translation.y = pos.y;

	Transform::update();
}

void PhysicsComponent::setRotation(const glm::quat& quat)
{
    // TO-DO: is this safe to do, or should we apply torque instead
    float angle = 2 * glm::acos(quat.w);
    m_body->SetTransform(m_body->GetPosition(), glm::radians(angle));
}

void PhysicsComponent::setTranslation(const glm::vec3& translation)
{
    // TO-DO: is this safe to do, or should we apply temporary linear velocity instead
    m_body->SetTransform(b2Vec2(translation.x,translation.y), m_body->GetAngle());
}

PhysicsData::PhysicsData(b2Shape* shape, float x, float y) :
    m_shape(shape),
    m_bodyType(b2_dynamicBody),
    m_categoryBits(PhysicsManager::COLLISION_DEFAULT),
    m_maskBits(PhysicsManager::MASK_DEFAULT),
    m_groupIndex(0),
    m_vx(0.0f),
    m_vy(0.0f),
	m_x(x),
	m_y(y)
{

}
