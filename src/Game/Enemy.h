#pragma once

#include "Common.h"
#include "Entity.h"
#include "StateMachine.h"

class ShootComponent;
class Timer;

class Enemy : public Entity
{
public:
	Enemy(COLOR color);
	virtual ~Enemy();
	virtual bool update();
	virtual void onCollide(EventObject* collider);

	glm::vec2 m_enemyDirection;

private:
	float m_health;
	ShootComponent* m_shootComponent;
	Timer* m_shootTimer;
	COLOR m_color;
};