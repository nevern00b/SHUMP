#pragma once

#include "Common.h"
#include "Entity.h"
#include "StateMachine.h"
#include "EnemyPool.h"

class ShootComponent;
class Timer;
class EnemyPool;
class EnemyPoolObj;

enum ENEMY_PATTERN
{
	STATIONARY,
	SIDE,
	HOVER,
	V_SHAPE,
	CLUSTER_1,
	CLUSTER_2
};

enum ENEMY_TYPE
{
	MISSILE,
	MELEE,
	EXPLOSIVE
};

class Enemy : public Entity
{
public:
	Enemy(COLOR color, ENEMY_PATTERN pattern, ENEMY_TYPE type, float pos_x);
	virtual ~Enemy();
	virtual bool update();
	virtual void onCollide(EventObject* collider);

	glm::vec2 m_enemyDirection;
	float m_brightness; // For animation;

	//Pool stuff
	virtual void create();
	virtual void destroy();
	virtual bool inUse();

	//void setEnemy(COLOR color, ENEMY_PATTERN pattern, ENEMY_TYPE type, float x);

private:

	void endIntro();
	bool m_intro;
	float m_health;
	ShootComponent* m_shootComponent;
	Timer* m_shootTimer;
	COLOR m_color;
	ENEMY_PATTERN m_pattern;
	ENEMY_TYPE m_type;
	float m_x;

	//Pool stuff
	bool m_inUse;
	Enemy* enemy;
};