#include "Enemy.h"

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

Enemy::Enemy() : Entity(0),
	m_health(2.0f),
	m_timer(0.0f)
{
	Material* material = Globals::m_dataManager->getMaterial("blue");
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

	//float currTime = Globals::m_uiManager->getTimeSinceBeginning();
	//if (currTime > m_timer)
	//{
	//	//printf("%f\n", (currTime - m_timer));
	//	m_timer += 0.3f; // Shoot every 0.3 seconds
	//
	//	b2Vec2 pos = m_physics->m_body->GetPosition();
	//	float vx = 0.0f;
	//	float vy = -5.0f;
	//	m_shootComponent->shoot(pos.x, pos.y, vx, vy);
	//}
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
