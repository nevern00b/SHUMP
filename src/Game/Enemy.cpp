#include "Enemy.h"

#include "Bullet.h"
#include "Globals.h"
#include "DataManager.h"
#include "Physics/PhysicsManager.h"
#include "Physics/PhysicsComponent.h"
#include "Rendering/RenderComponent.h"

Enemy::Enemy() : Entity(0),
	m_health(10.0f)
{
	Material* material = Globals::m_dataManager->getMaterial("blue");
	Mesh* mesh = Globals::m_dataManager->getMesh("cube");

	b2PolygonShape shape;
	shape.SetAsBox(0.5f, 0.5f);

	PhysicsData physicsData(shape, 0, 0);
	PhysicsComponent* physics = new PhysicsComponent(this, physicsData);
	RenderComponent* render = new RenderComponent(this, mesh, { material });
}

Enemy::~Enemy()
{

}

void Enemy::update()
{
	Entity::update();
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

void Enemy::onCollisionLeave(EventObject* collider)
{

}