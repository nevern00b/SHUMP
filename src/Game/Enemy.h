#pragma once

#include "Common.h"
#include "Entity.h"
#include "StateMachine.h"

class ShootComponent;
class Timer;

class Enemy : public Entity
{
public:
	Enemy(COLOR color, int pattern,int pos_x);
	virtual ~Enemy();
	virtual void update();

	virtual void onCollisionEnter(EventObject* collider);
	glm::vec2 enemyDirection;

private:
	float m_health;
	ShootComponent* m_shootComponent;
	Timer* m_shootTimer;
	COLOR m_color;
	int m_pattern;

	float m_x;
};