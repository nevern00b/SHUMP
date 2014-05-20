#pragma once

#include "Common.h"
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

private:
	Timer* m_timer;
	int pattern;
};