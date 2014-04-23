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
	COLOR getEnemyColor();

private:
	Timer* m_timer;
};