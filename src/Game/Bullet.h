#pragma once

#include <vector>
#include <Box2D/Box2D.h>
#include "Common.h"
#include "Rendering/ObjectPool.h"
#include "EventObject.h"
#include "BulletPool.h"
#include "StateMachine.h"

class Mesh;
class Material;
struct PhysicsData;
class Bullet;

class Bullet : public PoolObject
{

public:
	Bullet(const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef, COLOR color);
	virtual ~Bullet();

	virtual bool update();
	virtual void create(float x, float y, float vx, float vy);
	virtual glm::vec4 getTransform();


	b2Body* m_body;
	float m_damage;
	COLOR m_color;

};