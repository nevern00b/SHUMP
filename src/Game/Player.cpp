#include "Player.h"

#include <Box2D/Box2D.h>
#include "Rendering/Material.h"
#include "Utils.h"
#include "Globals.h"
#include "Physics/PhysicsComponent.h"
#include "Rendering/RenderComponent.h"
#include "Physics/PhysicsManager.h"
#include "DataManager.h"
#include "UIManager.h"
#include "StateMachine.h"
#include "Bullet.h"
#include "ShmupGame.h"
#include "BulletPool.h"
#include "ShootComponent.h"
#include "Item.h"

Player::Player() : Entity(0),
	m_lives(3)
{
	Material* material = new Material();
	material->m_noiseStrength = 0.15f;
    Mesh* mesh = Globals::m_dataManager->getMesh("sphere");

	b2PolygonShape shape;
	shape.SetAsBox(0.5f, 0.5f);

    PhysicsData physicsData(shape);
	physicsData.m_groupIndex = ShmupGame::PLAYER_GROUP;
	PhysicsComponent* physics = new PhysicsComponent(this, physicsData);
	RenderComponent* render = new RenderComponent(this, mesh, material);
	m_shootComponent = new ShootComponent(this, Globals::m_shmupGame->m_redBulletPool);

	m_shootTimer = new Timer(0.2f);

	changeColor(); // Sets color to default immunity state color
	
}

Player::~Player()
{

}

bool Player::update()
{
	if (!Entity::update()) return false;

	float speed = 10.0f;
	float vx = 0.0f;
	float vy = 0.0f;

    // Get keyboard input
    if (Globals::m_uiManager->isKeyDown(KEY_A))
        vx -= speed;
    if (Globals::m_uiManager->isKeyDown(KEY_D))
        vx += speed;
    if (Globals::m_uiManager->isKeyDown(KEY_W))
        vy += speed;
    if (Globals::m_uiManager->isKeyDown(KEY_S))
        vy -= speed;
	if (Globals::m_uiManager->isKeyDown(KEY_U))//Keyboard to take bullet change 
		Globals::m_stateMachine->changeBState(COLOR::RED);
	if (Globals::m_uiManager->isKeyDown(KEY_I))
		Globals::m_stateMachine->changeBState(COLOR::BLUE);
	if (Globals::m_uiManager->isKeyDown(KEY_O))
		Globals::m_stateMachine->changeBState(COLOR::GREEN);
	if (Globals::m_uiManager->isKeyDown(KEY_P))
		Globals::m_stateMachine->changeBState(COLOR::YELLOW);
	if (Globals::m_uiManager->isKeyDown(KEY_Y))
		Globals::m_stateMachine->checkStates();
	if (Globals::m_uiManager->isKeyDown(KEY_H))
		Globals::m_stateMachine->changeIState(COLOR::RED);
	if (Globals::m_uiManager->isKeyDown(KEY_J))
		Globals::m_stateMachine->changeIState(COLOR::BLUE);
	if (Globals::m_uiManager->isKeyDown(KEY_K))
		Globals::m_stateMachine->changeIState(COLOR::GREEN);
	if (Globals::m_uiManager->isKeyDown(KEY_L))
		Globals::m_stateMachine->changeIState(COLOR::YELLOW);

	//if (Globals::m_uiManager->isKeyPressed(KEY_SPACE))
	//{
	//	shoot();
	//	m_shootTimer->start();
	//}
	//
    //if (Globals::m_uiManager->isKeyDown(KEY_SPACE))
    //{
	//	if (m_shootTimer->checkInterval())
	//	{
	//		shoot();
	//	}
    //}

	// Auto shoot
	if (m_shootTimer->checkInterval())
	{
		shoot();
	}

	m_physics->applyVelocity(vx, vy);
	changeColor();

	return true;
}

void Player::onCollide(EventObject* collider)
{
	Bullet* bullet = dynamic_cast<Bullet*>(collider);
	ImmunityItem* immunityItem = dynamic_cast<ImmunityItem*>(collider);
	LifeItem* lifeItem = dynamic_cast<LifeItem*>(collider);

	if (bullet != 0)
	{
		bullet->destroy();

		if (bullet->m_color != Globals::m_stateMachine->getIState())
		{
			m_lives--;
			if (m_lives == 0)
			{
				destroy();
			}
			else
			{
				m_transform->setTranslation(0.0f, -5.0f);
			}
		}
	}
	else if (immunityItem != 0)
	{
		COLOR color = immunityItem->m_color;
		Globals::m_stateMachine->changeIState(color);
		Globals::m_stateMachine->changeBState(color);
		immunityItem->destroy();
	}
	else if (lifeItem != 0)
	{
		m_lives++;
		lifeItem->destroy();
	}

}

void Player::changeColor()
{
	COLOR immunState = Globals::m_stateMachine->getIState();
	m_render->m_materials[0]->setColor(immunState);
}


	

void Player::shoot()
{
	int bulletState = Globals::m_stateMachine->getBState();
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

void Player::gainLives(uint lives)
{
	m_lives += lives;
}