#include "Enemy.h"

#include "Bullet.h"
#include "Globals.h"
#include "DataManager.h"
#include "Physics/PhysicsManager.h"
#include "Physics/PhysicsComponent.h"
#include "Rendering/RenderComponent.h"
#include "ShmupGame.h"
#include "ShootComponent.h"

Enemy::Enemy() : Entity(0),
	m_health(10.0f),
	m_shootFrames(0)
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

	if (m_shootFrames % 20 == 0)
	{
		b2Vec2 pos = m_physics->m_body->GetPosition();
		float vx = 0.0f;
		float vy = -10.0f;
		m_shootComponent->shoot(pos.x, pos.y, vx, vy);
	}

	if (m_shootFrames % 100 == 0)
	{
		b2Vec2 pos = m_physics->m_body->GetPosition();
		m_shootComponent->shootRadial(pos.x, pos.y, 3, 10);
	}

	m_shootFrames++;
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
			destroy();
		}
	}
}
