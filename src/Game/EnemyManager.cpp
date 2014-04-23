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


			int type = getEnemyType();
			

			float x = glm::linearRand(-15.0f, 15.0f);
			float y = glm::linearRand(0.0f, 10.0f);

			pattern = 3;// glm::linearRand(1, 3);
			switch (pattern)
			{

			case 1: // get spawned from top and move either left,right
			{
						Enemy* enemy = new Enemy(type);
						enemy->m_transform->setTranslation(x, y);
						enemy->m_transform->setScale(0.5f);
						enemy->enemyDirection.x = glm::linearRand(-10.0f, 10.0f);
						enemy->enemyDirection.y = 10;
						break;
			}
			case 2: // hover only on top
			{
						Enemy* enemy = new Enemy(type);
						enemy->m_transform->setTranslation(x, y);
						enemy->m_transform->setScale(0.5f);
						enemy->enemyDirection.x = glm::linearRand(-10.0f, 10.0f);
						if (enemy->enemyDirection.x > -1.0f && enemy->enemyDirection.x < 1.0f) enemy->enemyDirection.x = -1.5f;
						enemy->enemyDirection.y = 0;
						break;
			}
			case 3: // form  V pattern
			{
						int xV = glm::linearRand(-10.0f, 10.0f);
						Enemy* enemy = new Enemy(type);
						enemy->m_transform->setTranslation(x, y);
						enemy->m_transform->setScale(0.5f);
						enemy->enemyDirection.x = xV;
						if (enemy->enemyDirection.x > -1.0f && enemy->enemyDirection.x < 1.0f) enemy->enemyDirection.x = -1.5f;
						enemy->enemyDirection.y = 0;

						Enemy* enemy1 = new Enemy(type);
						enemy1->m_transform->setTranslation(x+2, y+2);
						enemy1->m_transform->setScale(0.5f);
						enemy1->enemyDirection.x = xV;
						if (enemy1->enemyDirection.x > -1.0f && enemy1->enemyDirection.x < 1.0f) enemy1->enemyDirection.x = -1.5f;
						enemy1->enemyDirection.y = 0;

						Enemy* enemy2 = new Enemy(type);
						enemy2->m_transform->setTranslation(x+2, y-2);
						enemy2->m_transform->setScale(0.5f);
						enemy2->enemyDirection.x = xV;
						if (enemy2->enemyDirection.x > -1.0f && enemy2->enemyDirection.x < 1.0f) enemy2->enemyDirection.x = -1.5f;
						enemy2->enemyDirection.y = 0;

						Enemy* enemy3 = new Enemy(type);
						enemy3->m_transform->setTranslation(x + 4, y +4);
						enemy3->m_transform->setScale(0.5f);
						enemy3->enemyDirection.x = xV;
						if (enemy3->enemyDirection.x > -1.0f && enemy3->enemyDirection.x < 1.0f) enemy3->enemyDirection.x = -1.5f;
						enemy3->enemyDirection.y = 0;

						Enemy* enemy5 = new Enemy(type);
						enemy5->m_transform->setTranslation(x+4 , y -4);
						enemy5->m_transform->setScale(0.5f);
						enemy5->enemyDirection.x = xV;
						if (enemy5->enemyDirection.x > -1.0f && enemy5->enemyDirection.x < 1.0f) enemy5->enemyDirection.x = -1.5f;
						enemy5->enemyDirection.y = 0;

						break;
			}
			case 4: // form  V pattern
			{
						int xV = glm::linearRand(-10.0f, 10.0f);
						
						Enemy* enemy = new Enemy(type);
						enemy->m_transform->setTranslation(x, y);
						enemy->m_transform->setScale(0.5f);
						enemy->enemyDirection.x = xV;
						if (enemy->enemyDirection.x > -1.0f && enemy->enemyDirection.x < 1.0f) enemy->enemyDirection.x = -1.5f;
						enemy->enemyDirection.y = 0;

						Enemy* enemy1 = new Enemy(type);
						enemy1->m_transform->setTranslation(x - 2, y - 2);
						enemy1->m_transform->setScale(0.5f);
						enemy1->enemyDirection.x = xV;
						if (enemy1->enemyDirection.x > -1.0f && enemy1->enemyDirection.x < 1.0f) enemy1->enemyDirection.x = -1.5f;
						enemy1->enemyDirection.y = 0;

						Enemy* enemy2 = new Enemy(type);
						enemy2->m_transform->setTranslation(x + 2, y - 2);
						enemy2->m_transform->setScale(0.5f);
						enemy2->enemyDirection.x = xV;
						if (enemy2->enemyDirection.x > -1.0f && enemy2->enemyDirection.x < 1.0f) enemy2->enemyDirection.x = -1.5f;
						enemy2->enemyDirection.y = 0;

						Enemy* enemy3 = new Enemy(type);
						enemy3->m_transform->setTranslation(x - 4, y - 4);
						enemy3->m_transform->setScale(0.5f);
						enemy3->enemyDirection.x = xV;
						if (enemy3->enemyDirection.x > -1.0f && enemy3->enemyDirection.x < 1.0f) enemy3->enemyDirection.x = -1.5f;
						enemy3->enemyDirection.y = 0;

						Enemy* enemy5 = new Enemy(type);
						enemy5->m_transform->setTranslation(x + 4, y - 4);
						enemy5->m_transform->setScale(0.5f);
						enemy5->enemyDirection.x = xV;
						if (enemy5->enemyDirection.x > -1.0f && enemy5->enemyDirection.x < 1.0f) enemy5->enemyDirection.x = -1.5f;
						enemy5->enemyDirection.y = 0;

						break;
			}
			}

	}
}

int EnemyManager::getEnemyType()
{
	// Get the enemy type based off percent chance
	float rand = glm::linearRand(0.0f, 1.0f);
	int type = 1;

	if (rand < 0.4f) type = 1;
	else if (rand < 0.7f)type = 2;
	else if (rand < 0.9f) type = 3;
	else if (rand <= 1.0f) type = 4;
	return type;
}



