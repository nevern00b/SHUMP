#include "Bullet.h"

#include <Box2D/Box2D.h>
#include "Globals.h"
#include "Physics/PhysicsManager.h"
#include "Physics/PhysicsComponent.h"
#include "Rendering/Mesh.h"
#include "ShmupGame.h"
#include "UIManager.h"

Bullet::Bullet(const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef, COLOR color) : EventObject(),
	m_damage(1.0f),
	m_color(color)
{	
	m_body = Globals::m_physicsManager->m_world->CreateBody(&bodyDef);	
	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);
	m_body->SetActive(false);
	destroy();
}

Bullet::~Bullet()
{
	Globals::m_physicsManager->destroyBody(m_body);
}

bool Bullet::update()
{
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
	m_body->SetActive(true);
	m_disabled = false;

	float angle = glm::atan(vy, vx);
	m_body->SetTransform(b2Vec2(x, y), angle);
	m_body->SetLinearVelocity(b2Vec2(vx, vy));
}

void Bullet::destroy()
{
	m_disabled = true;
	// m_body is deactivated later outside of time step
}