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
#include <iostream>

EnemyManager::EnemyManager() 
{	
	m_timer = new Timer();
	m_timer->start(3.0f, true);
}

EnemyManager::~EnemyManager()
{

}

void EnemyManager::update()
{	
	if (m_timer->checkInterval())
	{
		// Get color randomly
		COLOR color = getEnemyColor();

		// Get type randomly
		ENEMY_TYPE type;
		float typeRand = glm::linearRand(0.0f, 1.0f);
		if (typeRand < 0.6f) type = ENEMY_TYPE::MISSILE;
		else if (typeRand < 0.8f) type = ENEMY_TYPE::MELEE;
		else if (typeRand <= 1.0f) type = ENEMY_TYPE::EXPLOSIVE;

		// Get pattern, partly based on the type
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
			if (patternRand < 0.6f) pattern = ENEMY_PATTERN::STATIONARY;
			else if (patternRand < 0.7f) pattern = ENEMY_PATTERN::HOVER;
			else if (patternRand < 0.8f) pattern = ENEMY_PATTERN::SIDE;
			else if (patternRand < 0.9f) pattern = ENEMY_PATTERN::V_SHAPE;
			else if (patternRand <= 1.0f) pattern = ENEMY_PATTERN::CLUSTER_1;
		}

		//pattern = ENEMY_PATTERN::STATIONARY;

		// Position
		float padding = 2.0f;
		float x = glm::linearRand(ShmupGame::WORLD_LOWER_BOUND_X + padding, ShmupGame::WORLD_UPPER_BOUND_X - padding);
		float y = glm::linearRand(0.0f, ShmupGame::WORLD_UPPER_BOUND_Y-10.0f);

		if (pattern == ENEMY_PATTERN::SIDE)
		{
			// get spawned from top and move either left,right
			Enemy* enemy = new Enemy(color,pattern,type,x);
			enemy->m_transform->setTranslation(x, y);
			enemy->m_enemyDirection.x = glm::linearRand(-1.0f, 1.0f);
			enemy->m_enemyDirection.y = -1.0f;
		}
		else if (pattern == ENEMY_PATTERN::HOVER)
		{
			Enemy* enemy = new Enemy(color,pattern,type,x);
			enemy->m_transform->setTranslation(x, y);
			enemy->m_enemyDirection.x = glm::linearRand(-10.0f, 10.0f);
			if (enemy->m_enemyDirection.x > -1.0f && enemy->m_enemyDirection.x < 1.0f) enemy->m_enemyDirection.x = -1.5f;
			enemy->m_enemyDirection.y = 0;
		}
		else if (pattern == ENEMY_PATTERN::V_SHAPE)
		{
			float xV = glm::linearRand(-10.0f, 10.0f);
			Enemy* enemy = new Enemy(color,pattern,type,x);
			enemy->m_transform->setTranslation(x, y);
			enemy->m_enemyDirection.x = xV;
			if (enemy->m_enemyDirection.x > -1.0f && enemy->m_enemyDirection.x < 1.0f) enemy->m_enemyDirection.x = -1.5f;
			enemy->m_enemyDirection.y = 0;

			Enemy* enemy1 = new Enemy(color,pattern,type,x);
			enemy1->m_transform->setTranslation(x + 2, y + 2);
			enemy1->m_enemyDirection.x = xV;
			if (enemy1->m_enemyDirection.x > -1.0f && enemy1->m_enemyDirection.x < 1.0f) enemy1->m_enemyDirection.x = -1.5f;
			enemy1->m_enemyDirection.y = 0;

			Enemy* enemy2 = new Enemy(color,pattern,type,x);
			enemy2->m_transform->setTranslation(x + 2, y - 2);
			enemy2->m_enemyDirection.x = xV;
			if (enemy2->m_enemyDirection.x > -1.0f && enemy2->m_enemyDirection.x < 1.0f) enemy2->m_enemyDirection.x = -1.5f;
			enemy2->m_enemyDirection.y = 0;

			Enemy* enemy3 = new Enemy(color,pattern,type,x);
			enemy3->m_transform->setTranslation(x + 4, y + 4);
			enemy3->m_enemyDirection.x = xV;
			if (enemy3->m_enemyDirection.x > -1.0f && enemy3->m_enemyDirection.x < 1.0f) enemy3->m_enemyDirection.x = -1.5f;
			enemy3->m_enemyDirection.y = 0;

			Enemy* enemy5 = new Enemy(color,pattern,type,x);
			enemy5->m_transform->setTranslation(x + 4, y - 4);
			enemy5->m_enemyDirection.x = xV;
			if (enemy5->m_enemyDirection.x > -1.0f && enemy5->m_enemyDirection.x < 1.0f) enemy5->m_enemyDirection.x = -1.5f;
			enemy5->m_enemyDirection.y = 0;
		}
		else if (pattern == ENEMY_PATTERN::CLUSTER_1) 
		{
			float xV = glm::linearRand(-10.0f, 10.0f);
						
			Enemy* enemy = new Enemy(color,pattern,type,x);
			enemy->m_transform->setTranslation(x, y);
			enemy->m_enemyDirection.x = xV;
			if (enemy->m_enemyDirection.x > -1.0f && enemy->m_enemyDirection.x < 1.0f) enemy->m_enemyDirection.x = -1.5f;
			enemy->m_enemyDirection.y = -10;

			Enemy* enemy1 = new Enemy(color,pattern,type,x);
			enemy1->m_transform->setTranslation(x + 2, y + 2);
			enemy1->m_enemyDirection.x = xV;
			if (enemy1->m_enemyDirection.x > -1.0f && enemy1->m_enemyDirection.x < 1.0f) enemy1->m_enemyDirection.x = -1.5f;
			enemy1->m_enemyDirection.y = -10;

			Enemy* enemy2 = new Enemy(color,pattern,type,x);
			enemy2->m_transform->setTranslation(x - 2, y + 2);
			enemy2->m_enemyDirection.x = xV;
			if (enemy2->m_enemyDirection.x > -1.0f && enemy2->m_enemyDirection.x < 1.0f) enemy2->m_enemyDirection.x = -1.5f;
			enemy2->m_enemyDirection.y = -10;

			Enemy* enemy3 = new Enemy(color,pattern,type,x);
			enemy3->m_transform->setTranslation(x + 4, y + 4);
			enemy3->m_enemyDirection.x = xV;
			if (enemy3->m_enemyDirection.x > -1.0f && enemy3->m_enemyDirection.x < 1.0f) enemy3->m_enemyDirection.x = -1.5f;
			enemy3->m_enemyDirection.y = -10;

			Enemy* enemy5 = new Enemy(color,pattern,type,x);
			enemy5->m_transform->setTranslation(x - 4, y + 4);
			enemy5->m_enemyDirection.x = xV;
			if (enemy5->m_enemyDirection.x > -1.0f && enemy5->m_enemyDirection.x < 1.0f) enemy5->m_enemyDirection.x = -1.5f;
			enemy5->m_enemyDirection.y = -10;
		}
		else if (pattern == ENEMY_PATTERN::CLUSTER_2)
		{
			float xV = glm::linearRand(-10.0f, 10.0f);

			Enemy* enemy = new Enemy(getEnemyColor(), pattern, type, x);
			enemy->m_transform->setTranslation(x, y);
			enemy->m_enemyDirection.x = xV;
			if (enemy->m_enemyDirection.x > -1.0f && enemy->m_enemyDirection.x < 1.0f) enemy->m_enemyDirection.x = -1.5f;
			enemy->m_enemyDirection.y = -10;

			Enemy* enemy1 = new Enemy(getEnemyColor(), pattern, type, x);
			enemy1->m_transform->setTranslation(x + 1, y);
			enemy1->m_enemyDirection.x = xV;
			if (enemy1->m_enemyDirection.x > -1.0f && enemy1->m_enemyDirection.x < 1.0f) enemy1->m_enemyDirection.x = -1.5f;
			enemy1->m_enemyDirection.y = -10;

			Enemy* enemy2 = new Enemy(getEnemyColor(), pattern, type, x);
			enemy2->m_transform->setTranslation(x - 1, y);
			enemy2->m_enemyDirection.x = xV;
			if (enemy2->m_enemyDirection.x > -1.0f && enemy2->m_enemyDirection.x < 1.0f) enemy2->m_enemyDirection.x = -1.5f;
			enemy2->m_enemyDirection.y = -10;

			Enemy* enemy3 = new Enemy(getEnemyColor(), pattern, type, x);
			enemy3->m_transform->setTranslation(x, y - 1);
			enemy3->m_enemyDirection.x = xV;
			if (enemy3->m_enemyDirection.x > -1.0f && enemy3->m_enemyDirection.x < 1.0f) enemy3->m_enemyDirection.x = -1.5f;
			enemy3->m_enemyDirection.y = -10;

			Enemy* enemy5 = new Enemy(getEnemyColor(), pattern, type, x);
			enemy5->m_transform->setTranslation(x, y + 1);
			enemy5->m_enemyDirection.x = xV;
			if (enemy5->m_enemyDirection.x > -1.0f && enemy5->m_enemyDirection.x < 1.0f) enemy5->m_enemyDirection.x = -1.5f;
			enemy5->m_enemyDirection.y = -10;
		}
		else if (pattern == ENEMY_PATTERN::STATIONARY)
		{
			Enemy* enemy = new Enemy(color, pattern, type, x);
			enemy->m_transform->setTranslation(x, ShmupGame::WORLD_UPPER_BOUND_Y);
			enemy->m_enemyDirection.x = 0;
			enemy->m_enemyDirection.y = -20;
		}

		//change enemy spawn rate
		int current_score = Globals::m_stateMachine->p_score;

		//score 100 = 1 second of gameplay
		//NOTE: score is based on things other than gameplay time. Should adjust these numbers below as necessary
		if (current_score < 1500) 
		{
			setSpawnRate(3.00f);
		}
		else if (current_score > 1500 && current_score < 2000) 
		{
			setSpawnRate(2.75f);
		} 
		else if (current_score > 2000 && current_score < 3000)
		{
			setSpawnRate(2.50f);
		}
		else if (current_score > 3000 && current_score < 6000)
		{
			setSpawnRate(2.25f);
		}
		else if (current_score > 6000 && current_score < 15000)
		{
			setSpawnRate(2.00f);
		}
		else if (current_score > 15000 && current_score < 18000)
		{
			setSpawnRate(1.50f);
		}
		else
		{
			setSpawnRate(1.00f);
		}

		//std::cout << "spawn rate: " << m_timer->m_interval << std::endl;
	}
}

COLOR EnemyManager::getEnemyColor()
{
	// Get the enemy color based off percent chance
	// Before red == 0.4, green = 0.7, blue = 0.9. Was there a reason to make them have unequal probabilities?
	float rand = glm::linearRand(0.0f, 1.0f);
	if (rand < 0.25f) return COLOR::RED;
	else if (rand < 0.50f) return COLOR::GREEN;
	else if (rand < 0.75f) return COLOR::BLUE;
	else if (rand <= 1.0f) return COLOR::YELLOW;
	else return COLOR::RED;
}

void EnemyManager::setSpawnRate(float m_interval)
{
	m_timer->setInterval(m_interval);
}