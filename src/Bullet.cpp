#include "Bullet.h"

#include <Box2D/Box2D.h>
#include "Material.h"
#include "Utils.h"
#include "Globals.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "PhysicsManager.h"
#include "DataManager.h"
#include "StateMachine.h"
#include "UIManager.h"

Bullet::Bullet(Entity* ship) : Entity(0)
{
	glm::vec3 playerPos = ship->getPosition();

	Material* material; 
	if (Globals::m_stateMachine->getBState() == 1)
		material = Globals::m_dataManager->getMaterial("red");
	else if (Globals::m_stateMachine->getBState() == 2)
		material = Globals::m_dataManager->getMaterial("blue");
	else if (Globals::m_stateMachine->getBState() == 3)
		material = Globals::m_dataManager->getMaterial("green");
	else if (Globals::m_stateMachine->getBState() == 4)
		material = Globals::m_dataManager->getMaterial("yellow");
	
	Mesh* mesh = Globals::m_dataManager->getMesh("cube");
	b2Shape* shape = Globals::m_physicsManager->m_squareSmall;
	PhysicsData physicsData(shape, playerPos.x, playerPos.y);
	physicsData.m_vx = 0.0f;
	physicsData.m_vy = 10.0f;
	PhysicsComponent* physics = new PhysicsComponent(this, physicsData);
	RenderComponent* render = new RenderComponent(this, mesh, { material });
	m_transform->setScale(0.1f);
}

Bullet::~Bullet()
{
	int debug = 0;
}

void Bullet::update()
{
	Entity::update();

	if (m_transform->m_translation.y > 5.0)
	{
		destroy();
	}
}