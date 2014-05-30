#include "EnemyPool.h"


EnemyPool::EnemyPool()
{

}


EnemyPool::~EnemyPool()
{
}

void EnemyPool::createPool(uint size)
{
	for (uint i = 0; i < size; i++)
	{
		float x = glm::linearRand(ShmupGame::WORLD_LOWER_BOUND_X + 2.0f, ShmupGame::WORLD_UPPER_BOUND_X - 2.0f);
		float y = glm::linearRand(0.0f, ShmupGame::WORLD_UPPER_BOUND_Y - 10.0f);

		Enemy* enemy = new Enemy(COLOR::RED, ENEMY_PATTERN::SIDE, ENEMY_TYPE::MISSILE, x);
		enemy->m_transform->setTranslation(x, y);
		enemy->m_enemyDirection.x = glm::linearRand(-1.0f, 1.0f);
		enemy->m_enemyDirection.y = -1.0f;
		poolA.push(enemy);
	}
}


Enemy* EnemyPool::getEnemy()
{
	return poolA.top();
}

bool EnemyPool::isEmpty()
{
	return poolA.empty();
}
