#pragma once
#include <iostream>
#include <stack>
#include "Enemy.h"

class EnemyPool
{
public:
	EnemyPool();
	virtual ~EnemyPool();

	Enemy* getEnemy();
	bool isEmpty();
	void createPool(uint size);

private:
	std::stack <Enemy*> poolA;
	std::stack <Enemy*> poolB;
};

