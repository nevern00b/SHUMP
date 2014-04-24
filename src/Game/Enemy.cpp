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

Enemy::Enemy(COLOR color, int pattern, int pos_x) : Entity(0),
m_color(color), m_pattern(pattern), m_x(pos_x)
{
	m_shootTimer = new Timer(0.3f);
	
	Material* material = Globals::m_dataManager->getMaterial(color);
	if (m_color == COLOR::RED)
	{
		m_health = 2.0f;
		m_shootComponent = new ShootComponent(this, Globals::m_shmupGame->m_enemyRBulletPool);
	}
	else if (m_color == COLOR::BLUE)
	{
		m_health = 4.0f;
		m_shootComponent = new ShootComponent(this, Globals::m_shmupGame->m_enemyBBulletPool);
	}
	else if (m_color == COLOR::GREEN)
	{
		m_health = 6.0f;
		m_shootComponent = new ShootComponent(this, Globals::m_shmupGame->m_enemyGBulletPool);
	}
	else if (m_color == COLOR::YELLOW)
	{
		m_health = 10.0f;
		m_shootComponent = new ShootComponent(this, Globals::m_shmupGame->m_enemyYBulletPool);
	}	
	
	Mesh* mesh = Globals::m_dataManager->getMesh("cube");

	b2PolygonShape shape;
	shape.SetAsBox(0.5f, 0.5f);
	PhysicsData physicsData(shape);
	physicsData.m_groupIndex = ShmupGame::ENEMY_GROUP;

	PhysicsComponent* physics = new PhysicsComponent(this, physicsData);
	RenderComponent* render = new RenderComponent(this, mesh, material);

	

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

	if (m_shootTimer->checkInterval())
	{
		b2Vec2 pos = m_physics->m_body->GetPosition();

		if (m_pattern == 2)
		{
			if (pos.x < (m_x - 3)) enemyDirection.x = -enemyDirection.x;
			else if (pos.x > (m_x + 3)) enemyDirection.x = -enemyDirection.x;
		}

		float vx;
		float vy;

		if (m_color == COLOR::RED)
		{
			vx = glm::linearRand(-5.0f, 5.0f);
			vy = glm::linearRand(-5.0f, 5.0f);

			if (vx == 0) vx = -1;
			if (vy == 0) vy = -1;
		}
		else if (m_color == COLOR::GREEN)
		{
			vx = glm::linearRand(-5.0f, 5.0f);
			vy = glm::linearRand(-5.0f, 5.0f);

			if (vx == 0) vx = -1;
			if (vy == 0) vy = -1;
		}
		else if (m_color == COLOR::BLUE)
		{
			vx = -pos.x;// glm::linearRand(-5.0f, 5.0f);
			vy = -pos.y;// glm::linearRand(-5.0f, 5.0f);
		}
		else if (m_color == COLOR::YELLOW)
		{
			vx = glm::linearRand(-5.0f, 5.0f);
			vy = glm::linearRand(-5.0f, 5.0f);
		}
		
		m_shootComponent->shoot(pos.x, pos.y, vx, vy);

		if (pos.x < -20 || pos.x > 20 || pos.y<-20 || pos.y >20)
			destroy();
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
		if (bullet->m_color != m_color){
			m_health -= bullet->m_damage;
			if (m_health <= 0.0f)
			{
				b2Vec2 pos = m_physics->m_body->GetPosition();
				Globals::m_shmupGame->m_particleSystem->createRadial(pos.x, pos.y, 10);
				
				destroy();
			}
		}
	}
}	
