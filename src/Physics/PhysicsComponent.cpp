#include "PhysicsComponent.h"

#include <Box2D/Box2D.h>
#include "PhysicsManager.h"
#include "Utils.h"
#include "Globals.h"
#include "Rendering/Mesh.h"
#include "Entity.h"
#include "Transform.h"

PhysicsComponent::PhysicsComponent(Entity* entity, const PhysicsData& physicsData) : Transform(entity)
{
	// Replace the default Transform
    delete entity->m_transform;
    entity->m_physics = this;
    entity->m_transform = this;

    // Create the b2body
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(physicsData.m_x, physicsData.m_y);
    bodyDef.linearVelocity = b2Vec2(physicsData.m_vx, physicsData.m_vy);
    bodyDef.type = physicsData.m_bodyType;
    bodyDef.userData = entity;
    bodyDef.fixedRotation = true;

    m_body = Globals::m_physicsManager->m_world->CreateBody(&bodyDef);

    // Create fixture and add to body
	b2FixtureDef fixtureDef;
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
	m_body->SetUserData(0);
	Globals::m_physicsManager->m_world->DestroyBody(m_body);
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
	//b2Vec2 pos = m_body->GetPosition();
	//float vx = translation.x - pos.x;
	//float vy = translation.y - pos.y;
	//setVelocity(vx, vy);
    // TO-DO: is this safe to do, or should we apply temporary linear velocity instead (above)
    m_body->SetTransform(b2Vec2(translation.x,translation.y), m_body->GetAngle());
}

void PhysicsComponent::setVelocity(float vx, float vy)
{
	m_body->SetLinearVelocity(b2Vec2(vx, vy));
}

void PhysicsComponent::applyVelocity(float vx, float vy)
{
	b2Vec2 vel = m_body->GetLinearVelocity();
	b2Vec2 desiredVel(vx, vy);
	b2Vec2 velChange = desiredVel - vel;
	b2Vec2 impulse = m_body->GetMass() * velChange;
	m_body->ApplyLinearImpulse(impulse, m_body->GetWorldCenter(), true);
}

PhysicsData::PhysicsData(b2Shape& shape) :
    m_shape(&shape),
    m_bodyType(b2_dynamicBody),
    m_categoryBits(PhysicsManager::COLLISION_DEFAULT),
    m_maskBits(PhysicsManager::MASK_DEFAULT),
    m_groupIndex(0),
    m_vx(0.0f),
    m_vy(0.0f),
	m_x(0.0f),
	m_y(0.0f)
{

}
