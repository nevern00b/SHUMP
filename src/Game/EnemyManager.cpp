#include "EnemyManager.h"

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

EnemyManager::EnemyManager() 
{	
	m_timer = new Timer(3.0f);

	m_health = 2.0f;
	
	arr[0] = 1; arr[1] = 3; arr[2] = 2; arr[3] = 1; arr[4] = 3;
	arr[5] = 1; arr[6] = 2; arr[7] = 4; arr[8] = 1; arr[9] = 1;
	
}

EnemyManager::~EnemyManager()
{

}

void EnemyManager::update()
{
	Entity::update();
	
	if (m_timer->checkInterval())
	{
		x = arr[(rand() % 9)];
		Enemy* enemy = new Enemy(x);
	}
	

}

int EnemyManager::Probabilty()
{

	int final_num;
	return final_num;
}


