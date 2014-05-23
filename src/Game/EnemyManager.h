#pragma once

#include "Common.h"
#include "Enemy.h"
#include "StateMachine.h"
class ShootComponent;
class Timer;

class EnemyManager

{
public:
	EnemyManager();
	~EnemyManager();
	void update();
	
	void setSpawnRate(float m_interval);
	COLOR getEnemyColor();
	ENEMY_TYPE changeEnemyType();
	ENEMY_PATTERN changeEnemyPattern();

private:
	Timer* m_timer;
	float spawn_rate;
	ENEMY_TYPE type;
	ENEMY_PATTERN pattern;
};