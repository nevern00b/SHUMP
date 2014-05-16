#include "Bullet.h"

#include <functional>
#include <Box2D/Box2D.h>
#include "Globals.h"
#include "Physics/PhysicsManager.h"
#include "Physics/PhysicsComponent.h"
#include "Rendering/Mesh.h"
#include "ShmupGame.h"
#include "UIManager.h"
#include "AnimationManager.h"

Bullet::Bullet(const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef, COLOR color) : PoolObject(),
	m_damage(1.0f),
	m_color(color),
	m_lifetime(0.0f)
{	
	m_body = Globals::m_physicsManager->m_world->CreateBody(&bodyDef);	
	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);
	m_body->SetActive(false);
}

Bullet::~Bullet()
{
	Globals::m_physicsManager->m_world->DestroyBody(m_body);
}

bool Bullet::update()
{
	b2Vec2 pos = m_body->GetPosition();
	if (pos.y > ShmupGame::WORLD_UPPER_BOUND_Y ||
		pos.y < ShmupGame::WORLD_LOWER_BOUND_Y-5.0 ||
		pos.x > ShmupGame::WORLD_UPPER_BOUND_X+5.0 ||
		pos.x < ShmupGame::WORLD_LOWER_BOUND_X-5.0 )
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
	m_lifetime = 0.0f;

	float angle = 0.0f;// glm::atan(vy, vx);
	m_body->SetTransform(b2Vec2(x, y), angle);
	m_body->SetLinearVelocity(b2Vec2(vx, vy));
}

glm::vec4 Bullet::getTransform()
{
	b2Vec2 pos = m_body->GetPosition();
	float angle = m_body->GetAngle();
	glm::vec4 transform(pos.x, pos.y, 0.0f, m_lifetime);
	return transform;
}

void Bullet::destroy()
{
	PoolObject::destroy();
	m_body->SetActive(false);
}

void Bullet::collide()
{
	//destroy();
	std::function<void()> callback = std::bind(&Bullet::destroy, this);
	new Animation(this, m_lifetime, 0.01f, 1.0f, 0.1f, 0.0f, false, callback);
	
	b2Vec2 pos = m_body->GetPosition();
	m_body->SetTransform(b2Vec2(pos.x, pos.y-1.0f), 0.0f);
	m_body->SetActive(false);

}