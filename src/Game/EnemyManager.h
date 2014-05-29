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

	Enemy* genEnemyHover(COLOR color, ENEMY_PATTERN pattern, ENEMY_TYPE type, float x, float y);
	Enemy* genEnemySide(COLOR color, ENEMY_PATTERN pattern, ENEMY_TYPE type, float x, float y);

	Enemy* genEnemyStationary(COLOR color, ENEMY_PATTERN pattern, ENEMY_TYPE type, float x, float y);
	Enemy* genEnemyMultiple(COLOR color, ENEMY_PATTERN pattern, ENEMY_TYPE type, float x, float y, float xV, float yV);

};