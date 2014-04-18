#pragma once

#include "Common.h"
#include "Entity.h"

class ShootComponent;
class Timer;

class Enemy : public Entity
{
public:
	Enemy();
	Enemy(int type);
	virtual ~Enemy();
	virtual void update();

	virtual void onCollisionEnter(EventObject* collider);

private:
	float m_health;
	ShootComponent* m_shootComponent;
	Timer* m_shootTimer;
	int m_type;
};