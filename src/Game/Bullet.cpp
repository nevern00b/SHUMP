#include "Bullet.h"

#include <Box2D/Box2D.h>
#include "Globals.h"
#include "Physics/PhysicsManager.h"
#include "Physics/PhysicsComponent.h"
#include "Rendering/Mesh.h"
#include "ShmupGame.h"

BulletPool::BulletPool(uint size, Mesh* mesh, Material* material, const PhysicsData& physicsData) : ObjectPool(size, mesh, material),
	m_bullets(size)
{	
	// Create the b2body
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(0.0f, 0.0f);
	bodyDef.linearVelocity = b2Vec2(0.0f, 0.0f);
	bodyDef.type = b2_dynamicBody;
	bodyDef.userData = this;
	bodyDef.fixedRotation = true;
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = physicsData.m_shape;
	fixtureDef.isSensor = true;
	fixtureDef.filter.categoryBits = physicsData.m_categoryBits;
	fixtureDef.filter.maskBits = physicsData.m_maskBits;
	fixtureDef.filter.groupIndex = physicsData.m_groupIndex;
	fixtureDef.userData = 0;

	for (uint i = 0; i < m_size; i++)
	{
		m_bullets[i] = new Bullet(bodyDef, fixtureDef);
	}
}

BulletPool::~BulletPool()
{
	for (uint i = 0; i < m_size; i++)
	{
		delete m_bullets[i];
	}
	m_bullets.clear();
}

void BulletPool::shoot(float x, float y, float vx, float vy)
{
	for (uint i = 0; i < m_size; i++)
	{
		Bullet* bullet = m_bullets[i];
		if (bullet->m_disabled)
		{
			bullet->create(x, y, vx, vy);
			break;
		}
	}
}

void BulletPool::render()
{
	uint count = 0;
	for (uint i = 0; i < m_size; i++)
	{
		Bullet* bullet = m_bullets[i];
		if (!bullet->m_disabled)
		{
			if (bullet->update())
			{
				b2Vec2 pos = bullet->m_body->GetPosition();
				float angle = bullet->m_body->GetAngle();
				glm::vec4 transform(pos.x, pos.y, 0.0f, angle);
				m_transformData[count] = transform;
				count++;
			}
		}
	}

	if (count == 0) return;
	m_transformBuffer->updateRange(0, count, &m_transformData[0], true);
	m_mesh->renderInstanced({ m_material }, count);
}

Bullet::Bullet(const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef) : EventObject(),
	m_damage(1.0f)
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
	if (pos.y > ShmupGame::WORLD_BOUND_Y)
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