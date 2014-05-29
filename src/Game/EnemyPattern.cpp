#include "EnemyPattern.h"

EnemyPattern::EnemyPattern()
{
}


EnemyPattern::~EnemyPattern()
{
}

void EnemyPattern::genEnemySide(COLOR color, ENEMY_PATTERN pattern, ENEMY_TYPE type, float x, float y)
{
	enemy = new Enemy(color, pattern, type, x);
	enemy->m_transform->setTranslation(x, y);
	enemy->m_enemyDirection.x = glm::linearRand(-1.0f, 1.0f);
	enemy->m_enemyDirection.y = -1.0f;
}

void EnemyPattern::genEnemyHover(COLOR color, ENEMY_PATTERN pattern, ENEMY_TYPE type, float x, float y)
{
	enemy = new Enemy(color, pattern, type, x);
	enemy->m_transform->setTranslation(x, y);
	enemy->m_enemyDirection.x = glm::linearRand(-10.0f, 10.0f);
	if (enemy->m_enemyDirection.x > -1.0f && enemy->m_enemyDirection.x < 1.0f) enemy->m_enemyDirection.x = -1.5f;
	enemy->m_enemyDirection.y = 0;
}

void EnemyPattern::genEnemyStationary(COLOR color, ENEMY_PATTERN pattern, ENEMY_TYPE type, float x, float y)
{
	enemy = new Enemy(color, pattern, type, x);
	enemy->m_transform->setTranslation(x, ShmupGame::WORLD_UPPER_BOUND_Y);
	enemy->m_enemyDirection.x = 0;
	enemy->m_enemyDirection.y = -20;
}

void EnemyPattern::genEnemyMultiple(COLOR color, ENEMY_PATTERN pattern, ENEMY_TYPE type, float x, float y, float xV, float yV)
{
	enemy = new Enemy(color, pattern, type, x);
	enemy->m_transform->setTranslation(x, y);
	enemy->m_enemyDirection.x = xV;
	if (enemy->m_enemyDirection.x > -1.0f && enemy->m_enemyDirection.x < 1.0f) enemy->m_enemyDirection.x = -1.5f;
	enemy->m_enemyDirection.y = yV;
}

void EnemyPattern::freeEnemy()
{
	delete enemy;
}