#pragma once

#include "Common.h"
#include "Entity.h"

class ShootComponent;

class Enemy : public Entity
{
public:
	Enemy();
	virtual ~Enemy();
	virtual void update();

	virtual void onCollisionEnter(EventObject* collider);

private:
	float m_health;
	ShootComponent* m_shootComponent;
	uint m_shootFrames;
};