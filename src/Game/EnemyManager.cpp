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

EnemyManager::EnemyManager() 
{	
	m_timer = new Timer(3.0f);
}

EnemyManager::~EnemyManager()
{

}

void EnemyManager::update()
{	
	if (m_timer->checkInterval())
	{
		float patternRand = glm::linearRand(0.0f, 1.0f);

		COLOR color = getEnemyColor();
			

		float x = glm::linearRand(-15.0f, 15.0f);
		float y = glm::linearRand(0.0f, 10.0f);


		pattern = 1;// glm::linearRand(1, 3);


		if (pattern == 1) // get spawned from top and move either left,right
		{
			Enemy* enemy = new Enemy(color,pattern,x);
			enemy->m_transform->setTranslation(x, y);
			enemy->m_enemyDirection.x = glm::linearRand(-1.0f, 1.0f);
			enemy->m_enemyDirection.y = 1.0f;
		}
		else if(pattern == 2) // hover only on top
		{
			Enemy* enemy = new Enemy(color,pattern,x);
			enemy->m_transform->setTranslation(x, y);
			enemy->m_enemyDirection.x = glm::linearRand(-10.0f, 10.0f);
			if (enemy->m_enemyDirection.x > -1.0f && enemy->m_enemyDirection.x < 1.0f) enemy->m_enemyDirection.x = -1.5f;
			enemy->m_enemyDirection.y = 0;
		}
		else if (pattern == 3) // form  V pattern
		{
			float xV = glm::linearRand(-10.0f, 10.0f);
			Enemy* enemy = new Enemy(color,pattern,x);
			enemy->m_transform->setTranslation(x, y);
			enemy->m_enemyDirection.x = xV;
			if (enemy->m_enemyDirection.x > -1.0f && enemy->m_enemyDirection.x < 1.0f) enemy->m_enemyDirection.x = -1.5f;
			enemy->m_enemyDirection.y = 0;

			Enemy* enemy1 = new Enemy(color,pattern,x);
			enemy1->m_transform->setTranslation(x + 2, y + 2);
			enemy1->m_enemyDirection.x = xV;
			if (enemy1->m_enemyDirection.x > -1.0f && enemy1->m_enemyDirection.x < 1.0f) enemy1->m_enemyDirection.x = -1.5f;
			enemy1->m_enemyDirection.y = 0;

			Enemy* enemy2 = new Enemy(color, pattern,x);
			enemy2->m_transform->setTranslation(x + 2, y - 2);
			enemy2->m_enemyDirection.x = xV;
			if (enemy2->m_enemyDirection.x > -1.0f && enemy2->m_enemyDirection.x < 1.0f) enemy2->m_enemyDirection.x = -1.5f;
			enemy2->m_enemyDirection.y = 0;

			Enemy* enemy3 = new Enemy(color,pattern,x);
			enemy3->m_transform->setTranslation(x + 4, y + 4);
			enemy3->m_enemyDirection.x = xV;
			if (enemy3->m_enemyDirection.x > -1.0f && enemy3->m_enemyDirection.x < 1.0f) enemy3->m_enemyDirection.x = -1.5f;
			enemy3->m_enemyDirection.y = 0;

			Enemy* enemy5 = new Enemy(color,pattern,x);
			enemy5->m_transform->setTranslation(x + 4, y - 4);
			enemy5->m_enemyDirection.x = xV;
			if (enemy5->m_enemyDirection.x > -1.0f && enemy5->m_enemyDirection.x < 1.0f) enemy5->m_enemyDirection.x = -1.5f;
			enemy5->m_enemyDirection.y = 0;
		}
		else if (pattern == 4)
		{
			float xV = glm::linearRand(-10.0f, 10.0f);
						
			Enemy* enemy = new Enemy(color,pattern,x);
			enemy->m_transform->setTranslation(x, y);
			enemy->m_enemyDirection.x = xV;
			if (enemy->m_enemyDirection.x > -1.0f && enemy->m_enemyDirection.x < 1.0f) enemy->m_enemyDirection.x = -1.5f;
			enemy->m_enemyDirection.y = 10;

			Enemy* enemy1 = new Enemy(color,pattern,x);
			enemy1->m_transform->setTranslation(x + 2, y + 2);
			enemy1->m_enemyDirection.x = xV;
			if (enemy1->m_enemyDirection.x > -1.0f && enemy1->m_enemyDirection.x < 1.0f) enemy1->m_enemyDirection.x = -1.5f;
			enemy1->m_enemyDirection.y = 10;

			Enemy* enemy2 = new Enemy(color,pattern,x);
			enemy2->m_transform->setTranslation(x - 2, y + 2);
			enemy2->m_enemyDirection.x = xV;
			if (enemy2->m_enemyDirection.x > -1.0f && enemy2->m_enemyDirection.x < 1.0f) enemy2->m_enemyDirection.x = -1.5f;
			enemy2->m_enemyDirection.y = 10;

			Enemy* enemy3 = new Enemy(color,pattern,x);
			enemy3->m_transform->setTranslation(x + 4, y + 4);
			enemy3->m_enemyDirection.x = xV;
			if (enemy3->m_enemyDirection.x > -1.0f && enemy3->m_enemyDirection.x < 1.0f) enemy3->m_enemyDirection.x = -1.5f;
			enemy3->m_enemyDirection.y = 10;

			Enemy* enemy5 = new Enemy(color,pattern,x);
			enemy5->m_transform->setTranslation(x - 4, y + 4);
			enemy5->m_enemyDirection.x = xV;
			if (enemy5->m_enemyDirection.x > -1.0f && enemy5->m_enemyDirection.x < 1.0f) enemy5->m_enemyDirection.x = -1.5f;
			enemy5->m_enemyDirection.y = 10;
		}
		else if (pattern == 5)
		{
			float xV = glm::linearRand(-10.0f, 10.0f);

			Enemy* enemy = new Enemy(getEnemyColor(), pattern, x);
			enemy->m_transform->setTranslation(x, y);
			enemy->m_enemyDirection.x = xV;
			if (enemy->m_enemyDirection.x > -1.0f && enemy->m_enemyDirection.x < 1.0f) enemy->m_enemyDirection.x = -1.5f;
			enemy->m_enemyDirection.y = 10;

			Enemy* enemy1 = new Enemy(getEnemyColor(), pattern, x);
			enemy1->m_transform->setTranslation(x + 1, y);
			enemy1->m_enemyDirection.x = xV;
			if (enemy1->m_enemyDirection.x > -1.0f && enemy1->m_enemyDirection.x < 1.0f) enemy1->m_enemyDirection.x = -1.5f;
			enemy1->m_enemyDirection.y = 10;

			Enemy* enemy2 = new Enemy(getEnemyColor(), pattern, x);
			enemy2->m_transform->setTranslation(x - 1, y);
			enemy2->m_enemyDirection.x = xV;
			if (enemy2->m_enemyDirection.x > -1.0f && enemy2->m_enemyDirection.x < 1.0f) enemy2->m_enemyDirection.x = -1.5f;
			enemy2->m_enemyDirection.y = 10;

			Enemy* enemy3 = new Enemy(getEnemyColor(), pattern, x);
			enemy3->m_transform->setTranslation(x, y - 1);
			enemy3->m_enemyDirection.x = xV;
			if (enemy3->m_enemyDirection.x > -1.0f && enemy3->m_enemyDirection.x < 1.0f) enemy3->m_enemyDirection.x = -1.5f;
			enemy3->m_enemyDirection.y = 10;

			Enemy* enemy5 = new Enemy(getEnemyColor(), pattern, x);
			enemy5->m_transform->setTranslation(x, y + 1);
			enemy5->m_enemyDirection.x = xV;
			if (enemy5->m_enemyDirection.x > -1.0f && enemy5->m_enemyDirection.x < 1.0f) enemy5->m_enemyDirection.x = -1.5f;
			enemy5->m_enemyDirection.y = 10;
		}
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