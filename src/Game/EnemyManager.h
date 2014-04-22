#pragma once

#include "Common.h"
class ShootComponent;
class Timer;

class EnemyManager

{
public:
	EnemyManager();
	~EnemyManager();
	void update();	
	int getEnemyType();

private:
	Timer* m_timer;
};