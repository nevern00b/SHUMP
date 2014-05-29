#include "EnemyPool.h"


EnemyPool::EnemyPool(uint size, float xpos)
{
	m_size = size;
	for (uint i = 0; i < m_size; i++)
	{
		m_enemies.push_back(new Enemy(COLOR::RED, ENEMY_PATTERN::SIDE, ENEMY_TYPE::MISSILE, xpos));
	}	
}

EnemyPool::~EnemyPool()
{
}

int EnemyPool::enemyAvailable()
{
	for (uint i = 0; i < m_size; i++)
	{
		if (!m_enemies[i]->inUse())
		{
			return i;
		}
	}
	return -1;
}

Enemy* EnemyPool::getEnemy(uint index)
{
	/*int index = enemyAvailable();
	if (index != -1)
	{
		m_enemies[index]->create();
		std::cout << "enemy created" << std::endl;
		return m_enemies[index];
	}
	std::cout << "pool extended" << std::endl;
	extend();
	return m_enemies[m_size - 1];*/
	std::cout << "enemy gotten" << std::endl;
	m_enemies[index]->create();
	return m_enemies[index];
}

void EnemyPool::extend()
{
	m_enemies.push_back(new Enemy(COLOR::RED, ENEMY_PATTERN::SIDE, ENEMY_TYPE::MISSILE, 10.0f));
    m_size++;
}
