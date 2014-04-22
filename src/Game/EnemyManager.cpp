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

		if (patternRand < 0.8) // Create single enemy;
		{
			int type = getEnemyType();
			Enemy* enemy = new Enemy(type);

			float x = glm::linearRand(-6.0f, 6.0f);
			float y = glm::linearRand(0.0f, 6.0f);

			enemy->m_transform->setTranslation(x, y);
			enemy->m_transform->setScale(0.5f);
		}
		else if (patternRand < 0.9) // Create V pattern of enemies
		{

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