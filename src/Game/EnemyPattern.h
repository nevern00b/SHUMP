#pragma once

#include "Enemy.h"

class EnemyPattern
{
private:
	EnemyPattern();
	Enemy* enemy;

public:
	~EnemyPattern();
	static void genEnemySide(COLOR color, ENEMY_PATTERN pattern, ENEMY_TYPE type, float x, float y);
	static void genEnemyHover(COLOR color, ENEMY_PATTERN pattern, ENEMY_TYPE type, float x, float y);
	static void genEnemyMultiple(COLOR color, ENEMY_PATTERN pattern, ENEMY_TYPE type, float x, float y, float xV, float yV);
	static void genEnemyStationary(COLOR color, ENEMY_PATTERN pattern, ENEMY_TYPE type, float x, float y);
	static void freeEnemy();
};

