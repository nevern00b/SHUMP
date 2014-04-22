#include "Enemy.h"

#include <Box2D/Box2D.h>
#include <glm/gtc/random.hpp>
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

Enemy::Enemy(int type) : Entity(0)
{
	m_shootTimer = new Timer(0.3f);
	
	m_type = type;
	Material* material;
	material = Globals::m_dataManager->getMaterial("white");
	switch (m_type)
	{
	case 1:
	{
	material = Globals::m_dataManager->getMaterial("red");
	m_health = 2.0f;
	break; 
	}
		
	case 2:
	{
	material = Globals::m_dataManager->getMaterial("green");
	m_health = 4.0f;
	break;
	}
	case 3:
	{
	material = Globals::m_dataManager->getMaterial("blue");
	m_health = 6.0f;
	break;
	}
	case 4:
	{
	material = Globals::m_dataManager->getMaterial("yellow");
	m_health = 10.0f;
	break;
	}
	}
	
	
	Mesh* mesh = Globals::m_dataManager->getMesh("cube");

	b2PolygonShape shape;
	shape.SetAsBox(0.5f, 0.5f);
	PhysicsData physicsData(shape);
	physicsData.m_groupIndex = ShmupGame::ENEMY_GROUP;

	PhysicsComponent* physics = new PhysicsComponent(this, physicsData);
	RenderComponent* render = new RenderComponent(this, mesh, { material });

	m_shootComponent = new ShootComponent(this, Globals::m_shmupGame->m_enemyBulletPool);
	
	float x = glm::linearRand(-6.0f, 6.0f);
	float y = glm::linearRand(0.0f, 6.0f);

	m_transform->setTranslation(x,y);
	m_transform->setScale(0.5f);
	
	
}

Enemy::~Enemy()
{

}

void Enemy::update()
{
	Entity::update();
	float vx, vy;

	if (m_shootTimer->checkInterval())
	{
		b2Vec2 pos = m_physics->m_body->GetPosition();

		switch (m_type)
		{
		case 1:
		{
			vx = glm::linearRand(-5.0f, 5.0f);
			vy = glm::linearRand(-5.0f, 5.0f);
			break;
		}

		case 2:
		{
			vx = glm::linearRand(-5.0f, 5.0f);
			vy = glm::linearRand(-5.0f, 5.0f);
			break;
		}
		case 3:
		{
			vx = -pos.x;
			vy = -pos.y;
			break;
		}
		case 4:
		{
			vx = -2.0f - pos.x;
			vy = -5.0f - pos.y;
			break;
		}
		}


		m_shootComponent->shoot(pos.x, pos.y, vx, vy);
	}	
}

void Enemy::onCollisionEnter(EventObject* collider)
{
	Bullet* bullet = dynamic_cast<Bullet*>(collider);
	if (bullet != 0)
	{
		bullet->destroy();
		m_health -= bullet->m_damage;
		if (m_health <= 0.0f)
		{
			b2Vec2 pos = m_physics->m_body->GetPosition();
			Globals::m_shmupGame->m_particleSystem->createRadial(pos.x, pos.y, 10);
			destroy();	
		}
	}
}
