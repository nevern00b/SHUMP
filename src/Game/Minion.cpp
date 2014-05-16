#include "Minion.h"

//#include <Box2D/Box2D.h>
#include "Rendering/Material.h"
#include "Globals.h"
#include "Physics/PhysicsComponent.h"
#include "Rendering/RenderComponent.h"
#include "Physics/PhysicsManager.h"
#include "DataManager.h"
#include "UIManager.h"
#include "ShmupGame.h"
#include "ShootComponent.h"
#include "Utils.h"
#include "Bullet.h"
#include "Item.h"
#include "Player.h"

Minion::Minion(b2Vec2 relativePos) : Entity(0), m_lives(1)
{
	Material* material = new Material();
	material->m_noiseStrength = 0.1f;
	material->m_spawnTime = Globals::m_uiManager->getTime();
	Mesh* mesh = Globals::m_dataManager->getMesh("sphere");

	b2PolygonShape shape; 
	shape.SetAsBox(0.5f, 0.5f);

	PhysicsData physicsData(shape);
	physicsData.m_groupIndex = ShmupGame::PLAYER_GROUP;
	PhysicsComponent* physics = new PhysicsComponent(this, physicsData);
	RenderComponent* render = new RenderComponent(this, mesh, material);
	m_shootComponent = new ShootComponent(this, Globals::m_shmupGame->m_redBulletPool);

	m_shootTimer = new Timer();
	m_shootTimer->start(0.2f, true);
	m_player = Globals::m_shmupGame->getPlayer();
	m_relativePos = relativePos;
}

Minion::~Minion()
{

}

bool Minion::update()
{
	if (!Entity::update()) return false;

	b2Vec2 pos = m_physics->m_body->GetPosition();
	b2Vec2 targetPos = m_player->getPosition2d() + m_relativePos;

	float speed = 10.0f;
	float vx = targetPos.x - pos.x;
	float vy = targetPos.y - pos.y;

	// Auto shoot
	if (m_shootTimer->checkInterval())
	{
		shoot();
	}

	m_physics->applyVelocity(vx, vy);

	return true;
}

void Minion::onCollide(EventObject* collider)
{
	Bullet* bullet = dynamic_cast<Bullet*>(collider);
	//ImmunityItem* immunityItem = dynamic_cast<ImmunityItem*>(collider);
	LifeItem* lifeItem = dynamic_cast<LifeItem*>(collider);

	if (bullet != 0)
	{
		bullet->destroy();

		if (bullet->m_color != Globals::m_stateMachine->getPlayerState())
		{
			m_lives--;
			if (m_lives == 0)
			{
				destroy();
				m_player->m_minionCount--;
			}
		}
	}
	/*else if (immunityItem != 0)
	{
		COLOR color = immunityItem->m_color;
		Globals::m_stateMachine->changeIState(color);
		Globals::m_stateMachine->changeBState(color);
		immunityItem->destroy();
	}*/
	else if (lifeItem != 0)
	{
		m_lives++;
		lifeItem->destroy();
	}

}


void Minion::shoot()
{
	int bulletState = Globals::m_stateMachine->getPlayerState();
	if (bulletState == COLOR::RED)
	{
		m_shootComponent->m_bulletPool = Globals::m_shmupGame->m_redBulletPool;
	}
	else if (bulletState == COLOR::BLUE)
	{
		m_shootComponent->m_bulletPool = Globals::m_shmupGame->m_blueBulletPool;
	}
	else if (bulletState == COLOR::GREEN)
	{
		m_shootComponent->m_bulletPool = Globals::m_shmupGame->m_greenBulletPool;
	}
	else if (bulletState == COLOR::YELLOW)
	{
		m_shootComponent->m_bulletPool = Globals::m_shmupGame->m_yellowBulletPool;
	}

	b2Vec2 pos = m_physics->m_body->GetPosition();
	float vx = 0.0f;
	float vy = 15.0f;
	m_shootComponent->shoot(pos.x, pos.y, vx, vy);
}
