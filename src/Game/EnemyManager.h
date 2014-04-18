#pragma once

#include "Common.h"
#include "Entity.h"
#include "Enemy.h"
class ShootComponent;

class EnemyManager : public Enemy

{
public:
	EnemyManager();
	virtual ~EnemyManager();
	virtual void update();
	int Probabilty();

	// = { 1, 3, 2, 1, 3, 1, 2, 4, 1, 1 };
	int arr[10];// = { 10, 20, 30 };
	

private:
	float m_health;
	float x = 1;

	ShootComponent* m_shootComponent;
	float m_timer;
};