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

Player::Player() : Entity(0),
	m_lives(3),
	m_reset(false)
{
	Material* material = new Material();
	material->m_diffuseBlend = 1.0f;
	material->m_diffuseTexture = Globals::m_dataManager->getTexture("noise");
	material->m_useNoise = true;

    Mesh* mesh = Globals::m_dataManager->getMesh("cube");

	b2PolygonShape shape;
	shape.SetAsBox(0.5f, 0.5f);

    PhysicsData physicsData(shape);
	physicsData.m_groupIndex = ShmupGame::PLAYER_GROUP;
	PhysicsComponent* physics = new PhysicsComponent(this, physicsData);
	RenderComponent* render = new RenderComponent(this, mesh, { material });
	m_shootComponent = new ShootComponent(this, Globals::m_shmupGame->m_redBulletPool);

	m_shootTimer = new Timer(0.2f);
	
}

Player::~Player()
{

}

void Player::update()
{
    Entity::update();

	if (m_reset)
	{
		m_reset = false;
		m_transform->setTranslation(0.0f, -5.0f);
	}

	float speed = 10.0f;
    b2Body* body = m_physics->m_body;

    b2Vec2 vel = body->GetLinearVelocity();
    b2Vec2 desiredVel(0, 0);

    // Get keyboard input
    if (Globals::m_uiManager->isKeyDown(GLFW_KEY_A))
        desiredVel.x -= speed;
    if (Globals::m_uiManager->isKeyDown(GLFW_KEY_D))
        desiredVel.x += speed;
    if (Globals::m_uiManager->isKeyDown(GLFW_KEY_W))
        desiredVel.y += speed;
    if (Globals::m_uiManager->isKeyDown(GLFW_KEY_S))
        desiredVel.y -= speed;
	if (Globals::m_uiManager->isKeyDown(GLFW_KEY_U))//Keyboard to take bullet change 
		Globals::m_stateMachine->changeBState(1);
	if (Globals::m_uiManager->isKeyDown(GLFW_KEY_I))
		Globals::m_stateMachine->changeBState(2);
	if (Globals::m_uiManager->isKeyDown(GLFW_KEY_O))
		Globals::m_stateMachine->changeBState(3);
	if (Globals::m_uiManager->isKeyDown(GLFW_KEY_P))
		Globals::m_stateMachine->changeBState(4);
	if (Globals::m_uiManager->isKeyDown(GLFW_KEY_Y))
		Globals::m_stateMachine->checkStates();
	if (Globals::m_uiManager->isKeyDown(GLFW_KEY_H))
		Globals::m_stateMachine->changeIState(1);
	if (Globals::m_uiManager->isKeyDown(GLFW_KEY_J))
		Globals::m_stateMachine->changeIState(2);
	if (Globals::m_uiManager->isKeyDown(GLFW_KEY_K))
		Globals::m_stateMachine->changeIState(3);
	if (Globals::m_uiManager->isKeyDown(GLFW_KEY_L))
		Globals::m_stateMachine->changeIState(4);

	if (Globals::m_uiManager->isKeyPressed(GLFW_KEY_SPACE))
	{
		shoot();
		m_shootTimer->start();
	}

    if (Globals::m_uiManager->isKeyDown(GLFW_KEY_SPACE))
    {
		if (m_shootTimer->checkInterval())
		{
			shoot();
		}
    }

	changeColor();
    b2Vec2 velChange = desiredVel - vel;
    b2Vec2 impulse = body->GetMass() * velChange;
    body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
}

void Player::changeColor()
{
	int immunState = Globals::m_stateMachine->getIState();
	Material* chmaterial = Globals::m_dataManager->getMaterial("blue");

	if (immunState == COLOR::RED)
	{
		chmaterial = Globals::m_dataManager->getMaterial("red");
		m_render->setMaterial(chmaterial);
	}
	else if (immunState == COLOR::BLUE)
	{
		chmaterial = Globals::m_dataManager->getMaterial("blue");
		m_render->setMaterial(chmaterial);
	}
	else if (immunState == COLOR::GREEN)
	{
		chmaterial = Globals::m_dataManager->getMaterial("green");
		m_render->setMaterial(chmaterial);
	}
	else if (immunState == COLOR::YELLOW)
	{
		chmaterial = Globals::m_dataManager->getMaterial("yellow");
		m_render->setMaterial(chmaterial);
	}

}

void Player::onCollisionEnter(EventObject* collider)
{
	Bullet* bullet = dynamic_cast<Bullet*>(collider);
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
				m_reset = true;
			}
		}
		else
		{

		}
	}
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