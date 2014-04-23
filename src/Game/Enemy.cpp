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
	
}

Enemy::~Enemy()
{

}

void Enemy::update()
{
	Entity::update();

	float speed = 10.0f;
	b2Body* body = m_physics->m_body;

	b2Vec2 vel = body->GetLinearVelocity();
	b2Vec2 desiredVel(0, 0);
	desiredVel.x = enemyDirection.x;
	desiredVel.y -= enemyDirection.y;


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
			if (vx == 0) vx = -1;
			if (vy == 0) vy = -1;
			break;
		}

		case 2:
		{
			vx = glm::linearRand(-5.0f, 5.0f);
			vy = glm::linearRand(-5.0f, 5.0f);
			if (vx == 0) vx = -1;
			if (vy == 0) vy = -1;
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

	b2Vec2 velChange = desiredVel-vel;
	b2Vec2 impulse = body->GetMass() * velChange;
	body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
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
