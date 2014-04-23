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
			COLOR color = getEnemyColor();
			Enemy* enemy = new Enemy(color);

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

COLOR EnemyManager::getEnemyColor()
{
	// Get the enemy type based off percent chance
	float rand = glm::linearRand(0.0f, 1.0f);
	COLOR type = COLOR::RED;

	if (rand < 0.4f) return COLOR::RED;
	else if (rand < 0.7f) return COLOR::GREEN;
	else if (rand < 0.9f) return COLOR::BLUE;
	else if (rand <= 1.0f) return COLOR::YELLOW;
}