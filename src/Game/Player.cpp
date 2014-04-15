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

Player::Player() : Entity(0)
{
	Material* material = Globals::m_dataManager->getMaterial("green");
    Mesh* mesh = Globals::m_dataManager->getMesh("cube");

	b2PolygonShape shape;
	shape.SetAsBox(0.5f, 0.5f);

    PhysicsData physicsData(shape, 0, -5);
	PhysicsComponent* physics = new PhysicsComponent(this, physicsData);
	RenderComponent* render = new RenderComponent(this, mesh, { material });
}

Player::~Player()
{

}

void Player::update()
{
    Entity::update();

	float speed = Globals::m_uiManager->getFramerateAdjust(10.0f);
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
	if (Globals::m_uiManager->isKeyDown(GLFW_KEY_U))
		Globals::m_stateMachine->changeBState(1);
	if (Globals::m_uiManager->isKeyDown(GLFW_KEY_I))
		Globals::m_stateMachine->changeBState(2);
	if (Globals::m_uiManager->isKeyDown(GLFW_KEY_O))
		Globals::m_stateMachine->changeBState(3);
	if (Globals::m_uiManager->isKeyDown(GLFW_KEY_P))
		Globals::m_stateMachine->changeBState(4);
	if (Globals::m_uiManager->isKeyDown(GLFW_KEY_Y))
		Globals::m_stateMachine->checkStates();

	if (Globals::m_uiManager->isKeyPressed(GLFW_KEY_SPACE))
	{
		m_shootFrames = 0;
		printf("start shoot/n");
	}

    if (Globals::m_uiManager->isKeyDown(GLFW_KEY_SPACE))
    {
        shoot();
    }


    b2Vec2 velChange = desiredVel - vel;
    b2Vec2 impulse = body->GetMass() * velChange;
    body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
}

void Player::shoot()
{
	if (m_shootFrames % 10 == 0)
	{
		b2Vec2 pos = m_physics->m_body->GetPosition();
		BulletPool* bulletPool = Globals::m_shmupGame->m_playerBulletPool;
		bulletPool->shoot(pos.x, pos.y, 0.0f, 20.0f);
	}

	m_shootFrames++;
	
}