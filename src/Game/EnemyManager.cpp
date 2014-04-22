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
		// Get the enemy type based off percent chance
		float rand = glm::linearRand(0.0f, 1.0f);
		int type = 1;

		if (rand < 0.4f) type = 1;
		else if (rand < 0.7f)type = 2;
		else if (rand < 0.9f) type = 3;
		else if (rand <= 1.0f) type = 4;

		Enemy* enemy = new Enemy(type);
	}
}
