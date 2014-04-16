#include "Bullet.h"

#include <Box2D/Box2D.h>
#include "Globals.h"
#include "Physics/PhysicsManager.h"
#include "Physics/PhysicsComponent.h"
#include "Rendering/Mesh.h"
#include "ShmupGame.h"
#include "UIManager.h"

Bullet::Bullet(const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef) : PoolObject(),
	m_damage(1.0f)
{	
	m_body = Globals::m_physicsManager->m_world->CreateBody(&bodyDef);	
	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);
	m_body->SetActive(false);
}

Bullet::~Bullet()
{
	Globals::m_physicsManager->destroyBody(m_body);
}

bool Bullet::update()
{
	// Deactivate body if it was marked as disabled
	if (m_disabled && m_body->IsActive())
	{
		m_body->SetActive(false);
		return false;
	}

	b2Vec2 pos = m_body->GetPosition();
	if (pos.y > ShmupGame::WORLD_BOUND_Y ||
		pos.y < -ShmupGame::WORLD_BOUND_Y ||
		pos.x > ShmupGame::WORLD_BOUND_X ||
		pos.x < -ShmupGame::WORLD_BOUND_X )
	{
		destroy();
		return false;
	}

	return true;
}

void Bullet::create(float x, float y, float vx, float vy)
{
	PoolObject::create(x, y, vx, vy);

	m_body->SetActive(true);

	float angle = glm::atan(vy, vx);
	m_body->SetTransform(b2Vec2(x, y), angle);
	m_body->SetLinearVelocity(b2Vec2(vx, vy));
}

glm::vec4 Bullet::getTransform()
{
	b2Vec2 pos = m_body->GetPosition();
	float angle = m_body->GetAngle();
	glm::vec4 transform(pos.x, pos.y, 0.0f, angle);
	return transform;
}