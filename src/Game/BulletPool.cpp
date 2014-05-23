#include "BulletPool.h"

#include "Bullet.h"
#include "Physics/PhysicsComponent.h"
#include "Rendering/Mesh.h"
#include "Rendering/Buffer.h"
#include "StateMachine.h"

BulletPool::BulletPool(uint size, Mesh* mesh, Material* material, const PhysicsData& physicsData, COLOR color) : ObjectPool(size, mesh, material)
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
		m_objects[i] = new Bullet(bodyDef, fixtureDef, color);
	}
}

BulletPool::~BulletPool()
{
	
}

