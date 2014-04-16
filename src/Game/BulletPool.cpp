#include "BulletPool.h"

#include "Bullet.h"
#include "Physics/PhysicsComponent.h"
#include "Rendering/Mesh.h"
#include "Rendering/Buffer.h"
#include "StateMachine.h"

BulletPool::BulletPool(uint size, Mesh* mesh, Material* material, const PhysicsData& physicsData, COLOR color) : ObjectPool(size, mesh, material),
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
		m_bullets[i] = new Bullet(bodyDef, fixtureDef, color);
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
	m_mesh->renderInstanced({ m_material }, count, m_transformBuffer->m_bufferObject);
}