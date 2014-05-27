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
}

EnemyManager::~EnemyManager()
{

}

void EnemyManager::update()
{	
	if (m_timer->checkInterval())
	{
		COLOR color = getEnemyColor();
		type = changeEnemyType();
		pattern = changeEnemyPattern();

		// Position
		float padding = 2.0f;
		float x = glm::linearRand(ShmupGame::WORLD_LOWER_BOUND_X + padding, ShmupGame::WORLD_UPPER_BOUND_X - padding);
		float y = glm::linearRand(0.0f, ShmupGame::WORLD_UPPER_BOUND_Y-10.0f);

		if (pattern == ENEMY_PATTERN::SIDE)
		{
			// get spawned from top and move either left, right 
			// Note: side to side movement a bit slow?
			EnemyPattern::genEnemySide(color, pattern, type, x, y);
		}
		else if (pattern == ENEMY_PATTERN::HOVER)
		{
			//Goes side to side @ random speed
			EnemyPattern::genEnemyHover(color, pattern, type, x, y);

		}
		else if (pattern == ENEMY_PATTERN::V_SHAPE)
		{
			//V-shape, side to side
			float xV = glm::linearRand(-10.0f, 10.0f);
			EnemyPattern::genEnemyMultiple(color, pattern, type, x, y, xV, 0);
			EnemyPattern::genEnemyMultiple(color, pattern, type, x + 2, y + 2, xV, 0);
			EnemyPattern::genEnemyMultiple(color, pattern, type, x + 2, y - 2, xV, 0);
			EnemyPattern::genEnemyMultiple(color, pattern, type, x + 4, y + 4, xV, 0);
			EnemyPattern::genEnemyMultiple(color, pattern, type, x + 4, y - 4, xV, 0);
		}
		else if (pattern == ENEMY_PATTERN::CLUSTER_1) 
		{
			//V-shape heading towards the player
			float xV = glm::linearRand(-10.0f, 10.0f);
			EnemyPattern::genEnemyMultiple(color, pattern, type, x, y, xV, -10);
			EnemyPattern::genEnemyMultiple(color, pattern, type, x + 2, y + 2, xV, -10);
			EnemyPattern::genEnemyMultiple(color, pattern, type, x + 2, y - 2, xV, -10);
			EnemyPattern::genEnemyMultiple(color, pattern, type, x + 4, y + 4, xV, -10);
			EnemyPattern::genEnemyMultiple(color, pattern, type, x + 4, y - 4, xV, -10);

		}
		else if (pattern == ENEMY_PATTERN::CLUSTER_2)
		{
			//Interesting pattern. Multiple cells cluster together tightly, with one as the "nucleus" or center 
			float xV = glm::linearRand(-10.0f, 10.0f);
			EnemyPattern::genEnemyMultiple(color, pattern, type, x, y, xV, -10);
			EnemyPattern::genEnemyMultiple(color, pattern, type, x + 1, y, xV, -10);
			EnemyPattern::genEnemyMultiple(color, pattern, type, x - 1, y, xV, -10);
			EnemyPattern::genEnemyMultiple(color, pattern, type, x, y -1, xV, -10);
			EnemyPattern::genEnemyMultiple(color, pattern, type, x, y + 1, xV, -10);
		}
		else if (pattern == ENEMY_PATTERN::STATIONARY)
		{
			EnemyPattern::genEnemyStationary(color, pattern, type, x, y);
		}

		//change enemy spawn rate based on score. Should adjust these numbers as necessary
		int current_score = Globals::m_stateMachine->p_score;
		spawn_rate = Globals::m_stateMachine->changeEnemySpawnRate(current_score);
		setSpawnRate(spawn_rate);
		
		//std::cout << "spawn rate: " << m_timer->m_interval << std::endl;
	}
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
	else if (typeRand <= 1.0f) return ENEMY_TYPE::EXPLOSIVE;
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
