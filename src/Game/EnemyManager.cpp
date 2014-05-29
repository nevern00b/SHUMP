#include "EnemyManager.h"
#include <glm/gtc/random.hpp>
#include <Box2D/Box2D.h>
#include "Bullet.h"
#include "Globals.h"
#include "DataManager.h"
#include "Physics/PhysicsManager.h"
#include "Physics/PhysicsComponent.h"
#include "Rendering/RenderComponent.h"
#include "ShmupGame.h"
#include "ShootComponent.h"
#include "UIManager.h"
#include "Rendering/ParticleSystem.h"
#include "Enemy.h"
#include "EnemyPattern.h"
#include <iostream>

EnemyManager::EnemyManager() 
{	
	m_timer = new Timer();
	m_timer->start(3.0f, true);
	//Should init enemy pool here
	epool = new EnemyPool(10);
}

EnemyManager::~EnemyManager()
{

}

bool EnemyManager::update()
{	
	bool checked = m_timer->checkInterval();
	if (checked && Globals::m_stateMachine->p_score)
	{
		COLOR color = getEnemyColor();
		type = changeEnemyType();
		//pattern = changeEnemyPattern();
		pattern = ENEMY_PATTERN::SIDE;

		// Position
		float padding = 2.0f;
		float x = glm::linearRand(ShmupGame::WORLD_LOWER_BOUND_X + padding, ShmupGame::WORLD_UPPER_BOUND_X - padding);
		float y = glm::linearRand(0.0f, ShmupGame::WORLD_UPPER_BOUND_Y - 10.0f);
		if (pattern == ENEMY_PATTERN::SIDE)
		{
			// get spawned from top and move either left, right 
			// Note: side to side movement a bit slow?
			int index = epool->enemyAvailable();
			if (index != -1)
			{
				currentEnemy = epool->getEnemy(index);
				processEnemySide(currentEnemy, x, y);
			}
			//genEnemySide(currentEnemy);
			//currentEnemy = genEnemySide(color, pattern, type, x, y);
		}
		else if (pattern == ENEMY_PATTERN::HOVER)
		{
			//Goes side to side @ random speed
			genEnemyHover(color, pattern, type, x, y);

		}
		else if (pattern == ENEMY_PATTERN::V_SHAPE)
		{
			//V-shape, side to side
			float xV = glm::linearRand(-10.0f, 10.0f);
			genEnemyMultiple(color, pattern, type, x, y, xV, 0);
			genEnemyMultiple(color, pattern, type, x + 2, y + 2, xV, 0);
			genEnemyMultiple(color, pattern, type, x + 2, y - 2, xV, 0);
			genEnemyMultiple(color, pattern, type, x + 4, y + 4, xV, 0);
			genEnemyMultiple(color, pattern, type, x + 4, y - 4, xV, 0);
		}
		else if (pattern == ENEMY_PATTERN::CLUSTER_1) 
		{
			//V-shape heading towards the player
			float xV = glm::linearRand(-10.0f, 10.0f);
			genEnemyMultiple(color, pattern, type, x, y, xV, -10);
			genEnemyMultiple(color, pattern, type, x + 2, y + 2, xV, -10);
			genEnemyMultiple(color, pattern, type, x + 2, y - 2, xV, -10);
			genEnemyMultiple(color, pattern, type, x + 4, y + 4, xV, -10);
			genEnemyMultiple(color, pattern, type, x + 4, y - 4, xV, -10);

		}
		else if (pattern == ENEMY_PATTERN::CLUSTER_2)
		{
			//Interesting pattern. Multiple cells cluster together tightly, with one as the "nucleus" or center 
			float xV = glm::linearRand(-10.0f, 10.0f);
			genEnemyMultiple(color, pattern, type, x, y, xV, -10);
			genEnemyMultiple(color, pattern, type, x + 1, y, xV, -10);
			genEnemyMultiple(color, pattern, type, x - 1, y, xV, -10);
			genEnemyMultiple(color, pattern, type, x, y -1, xV, -10);
			genEnemyMultiple(color, pattern, type, x, y + 1, xV, -10);
		}
		else if (pattern == ENEMY_PATTERN::STATIONARY)
		{
			genEnemyStationary(color, pattern, type, x, y);
		}

		//change enemy spawn rate based on score. Should adjust these numbers as necessary
		int current_score = Globals::m_stateMachine->p_score;
		spawn_rate = Globals::m_stateMachine->changeEnemySpawnRate(current_score);
		setSpawnRate(spawn_rate);
		
		//std::cout << "spawn rate: " << m_timer->m_interval << std::endl;
		return true;
	}
	return false;
}

COLOR EnemyManager::getEnemyColor()
{
	// Get the enemy color based off percent chance
	float rand = glm::linearRand(0.0f, 1.0f);
	if (rand < 0.4f) return COLOR::RED;
	else if (rand < 0.7f) return COLOR::GREEN;
	else if (rand < 0.9f) return COLOR::BLUE;
	else if (rand <= 1.0f) return COLOR::YELLOW;
	else return COLOR::RED;
}

ENEMY_TYPE EnemyManager::changeEnemyType()
{
	float typeRand = glm::linearRand(0.0f, 1.0f);
	if (typeRand < 0.6f) return ENEMY_TYPE::MISSILE;
	else if (typeRand < 0.8f) return ENEMY_TYPE::MELEE;
	else return ENEMY_TYPE::EXPLOSIVE;
}

ENEMY_PATTERN EnemyManager::changeEnemyPattern()
{
	ENEMY_PATTERN pattern = ENEMY_PATTERN::SIDE;
	if (type == ENEMY_TYPE::EXPLOSIVE)
	{
		pattern = ENEMY_PATTERN::HOVER;
	}
	else if (type == ENEMY_TYPE::MELEE)
	{
		pattern = ENEMY_PATTERN::HOVER;
	}
	else if (type == ENEMY_TYPE::MISSILE)
	{
		float patternRand = glm::linearRand(0.0f, 1.0f);
		if (patternRand < 0.5f) pattern = ENEMY_PATTERN::STATIONARY;
		else if (patternRand < 0.6f) pattern = ENEMY_PATTERN::HOVER;
		else if (patternRand < 0.7f) pattern = ENEMY_PATTERN::SIDE;
		else if (patternRand < 0.8f) pattern = ENEMY_PATTERN::V_SHAPE;
		else if (patternRand < 0.9f) pattern = ENEMY_PATTERN::CLUSTER_1;
		else pattern = ENEMY_PATTERN::CLUSTER_2;
	}
	return pattern;
}

void EnemyManager::setSpawnRate(float m_interval)
{
	m_timer->setInterval(m_interval);
}

Enemy* EnemyManager::genEnemySide(COLOR color, ENEMY_PATTERN pattern, ENEMY_TYPE type, float x, float y)
{
	Enemy* enemy = new Enemy(color, pattern, type, x);
	enemy->m_transform->setTranslation(x, y);
	enemy->m_enemyDirection.x = glm::linearRand(-1.0f, 1.0f);
	enemy->m_enemyDirection.y = -1.0f;
	return enemy;
}

Enemy* EnemyManager::genEnemyHover(COLOR color, ENEMY_PATTERN pattern, ENEMY_TYPE type, float x, float y)
{
	Enemy* enemy = new Enemy(color, pattern, type, x);
	enemy->m_transform->setTranslation(x, y);
	enemy->m_enemyDirection.x = glm::linearRand(-10.0f, 10.0f);
	if (enemy->m_enemyDirection.x > -1.0f && enemy->m_enemyDirection.x < 1.0f) enemy->m_enemyDirection.x = -1.5f;
	enemy->m_enemyDirection.y = 0;
	return enemy;
}

Enemy* EnemyManager::genEnemyStationary(COLOR color, ENEMY_PATTERN pattern, ENEMY_TYPE type, float x, float y)
{
	Enemy* enemy = new Enemy(color, pattern, type, x);
	enemy->m_transform->setTranslation(x, ShmupGame::WORLD_UPPER_BOUND_Y);
	enemy->m_enemyDirection.x = 0;
	enemy->m_enemyDirection.y = -20;
	return enemy;
}

Enemy* EnemyManager::genEnemyMultiple(COLOR color, ENEMY_PATTERN pattern, ENEMY_TYPE type, float x, float y, float xV, float yV)
{
	Enemy* enemy = new Enemy(color, pattern, type, x);
	enemy->m_transform->setTranslation(x, y);
	enemy->m_enemyDirection.x = xV;
	if (enemy->m_enemyDirection.x > -1.0f && enemy->m_enemyDirection.x < 1.0f) enemy->m_enemyDirection.x = -1.5f;
	enemy->m_enemyDirection.y = yV;
	return enemy;
}

void EnemyManager::processEnemySide(Enemy* enemy, float x, float y)
{
	enemy->m_render->render();
	enemy->setEnemy(x);
	enemy->m_transform->setTranslation(x, y);
	enemy->m_enemyDirection.x = glm::linearRand(-1.0f, 1.0f);
	enemy->m_enemyDirection.y = -1.0f;
}
