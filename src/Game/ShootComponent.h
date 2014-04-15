#pragma once

#include "Component.h"
#include "Common.h"

class Entity;
struct PhysicsData;
class BulletPool;

class ShootComponent : public Component
{
public:
	ShootComponent(Entity* entity, BulletPool* bulletPool);
	virtual ~ShootComponent();

	void shoot(float x, float y, float vx, float vy);
	void shootRadial(float x, float y, float speed, uint count);

	BulletPool* m_bulletPool;
};