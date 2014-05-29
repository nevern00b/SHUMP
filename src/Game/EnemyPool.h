#pragma once
#include "Rendering/ObjectPool.h"
#include "Globals.h"
#include "Enemy.h"
#include "EventObject.h"
#include "Common.h"
#include <vector>

class Enemy;

class EnemyPool
{
public:
	EnemyPool(uint size);
	~EnemyPool();

	int enemyAvailable();
	Enemy* getEnemy(uint index);
	void extend();
private:
	std::vector <Enemy*> m_enemies;
	uint m_size;
	//EnemyPoolObj* head;
	//EnemyPoolObj* tail;
};

//class EnemyPoolObj
//{
//public:
//	EnemyPoolObj();
//	virtual ~EnemyPoolObj();
//
//	virtual void create();
//	virtual void destroy();
//
//	Enemy* returnEnemy();
//	virtual bool inUse();
//	virtual void extend();
//
//private:
//	bool m_inUse;
//	Enemy* enemy;
//
//	//EnemyPoolObj* next;
//	//void setNext(EnemyPoolObj* obj);
//};