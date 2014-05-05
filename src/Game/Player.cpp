#include "Player.h"


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
#include "StateMachine.h"
#include <glm/gtc/random.hpp>
#include "Minion.h"

Player::Player() : Entity(0), m_lives(3), m_minionCount(0)
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

	m_shootTimer = new Timer();
	m_shootTimer->start(0.1f, true);

	changeColor(); // Sets color to default immunity state color	
}

Player::~Player()
{
	Globals::m_shmupGame->m_player = 0;
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
		Globals::m_stateMachine->changePlayerState(COLOR::RED);
	if (Globals::m_uiManager->isKeyDown(KEY_I))
		Globals::m_stateMachine->changePlayerState(COLOR::BLUE);
	if (Globals::m_uiManager->isKeyDown(KEY_O))
		Globals::m_stateMachine->changePlayerState(COLOR::GREEN);
	if (Globals::m_uiManager->isKeyDown(KEY_P))
		Globals::m_stateMachine->changePlayerState(COLOR::YELLOW);
	if (Globals::m_uiManager->isKeyDown(KEY_Y))
		Globals::m_stateMachine->checkStates();
	
	// Check if the mouse dragged
	if (Globals::m_uiManager->isMouseDragging())
	{
		uint oldMouseX = Globals::m_uiManager->m_oldMouseX;
		uint oldMouseY = Globals::m_uiManager->m_oldMouseY;
		uint newMouseX = Globals::m_uiManager->m_mouseX;
		uint newMouseY = Globals::m_uiManager->m_mouseY;

		Ray rOld = Utils::getPickingRay(oldMouseX, oldMouseY);
		Ray rNew = Utils::getPickingRay(newMouseX, newMouseY);
		glm::vec3 posOld = rOld.m_position + (-rOld.m_position.z / rOld.m_direction.z) * rOld.m_direction;
		glm::vec3 posNew = rNew.m_position + (-rNew.m_position.z / rNew.m_direction.z) * rNew.m_direction;
		glm::vec3 translation = posNew - posOld;
		m_physics->translate(translation);
	}

	m_physics->applyVelocity(vx, vy);

	//if (Globals::m_uiManager->isKeyPressed(GLFW_KEY_SPACE))
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

	
	changeColor();

	return true;
}

b2Vec2 Player::getPosition2d()
{
	b2Vec2 pos = m_physics->m_body->GetPosition();
	return pos;
}

void Player::onCollide(EventObject* collider)
{
	Bullet* bullet = dynamic_cast<Bullet*>(collider);
	ImmunityItem* immunityItem = dynamic_cast<ImmunityItem*>(collider);
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
			}
			else
			{
				m_transform->setTranslation(0.0f, -5.0f);
			}
		}
	}
	else if (immunityItem != 0)
	{
		Globals::m_stateMachine->p_score = Globals::m_stateMachine->p_score + 250;
		COLOR color = immunityItem->m_color;
		Globals::m_stateMachine->changePlayerState(color);
		immunityItem->destroy();
	}
	else if (lifeItem != 0)
	{
		Globals::m_stateMachine->p_score = Globals::m_stateMachine->p_score + 1000;
		m_lives++;
		lifeItem->destroy();
	}

}

void Player::changeColor()
{
	COLOR immunState = Globals::m_stateMachine->getPlayerState();
	m_render->m_materials[0]->setColor(immunState);
}


void Player::shoot()
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
	float vy = 30.0f;
	m_shootComponent->shoot(pos.x, pos.y, vx, vy);
	m_shootComponent->shoot(pos.x, pos.y, -1.0f, vy);
	m_shootComponent->shoot(pos.x, pos.y, 1.0f, vy);

}

void Player::gainLives(uint lives)
{
	m_lives += lives;
}

void Player::gainMinions(uint newMinions)
{
	int oldMinionCount = m_minionCount;
	int newMinionCount = m_minionCount + newMinions;
	m_minionCount = newMinionCount <= Max_Minion_Count ? newMinionCount : Max_Minion_Count;
	for (int i = 0; i < m_minionCount - oldMinionCount; i++)
	{
		float x = glm::linearRand(-2.0f, 2.0f);
		float y = glm::linearRand(-2.0f, 0.0f);
		Minion* newMinion = new Minion(b2Vec2(x, y));
	}
}