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

#include <iostream>

Player::Player() : Entity(0), m_lives(3), m_minionCount(0)
{
	Material* material = new Material();
	material->m_noiseStrength = 0.15f;
	material->m_specPower = 10.0f;
	material->m_specIntensity = 0.5f;
	//material->m_diffuseColor.a = 0.5;
    Mesh* mesh = Globals::m_dataManager->getMesh("sphere");

	b2PolygonShape shape;
	shape.SetAsBox(0.5f, 0.5f);

    PhysicsData physicsData(shape);
	physicsData.m_groupIndex = ShmupGame::PLAYER_GROUP;
	PhysicsComponent* physics = new PhysicsComponent(this, physicsData);
	RenderComponent* render = new RenderComponent(this, mesh, material);
	m_shootComponent = new ShootComponent(this, Globals::m_shmupGame->m_redBulletPool);

	m_shootRadial = false;
	m_shootTimer = new Timer();
	m_shootTimer->start(0.25f, true);

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

	//Change bullet stream width with number keys
	if (Globals::m_uiManager->isKeyDown(GLFW_KEY_1))
		Globals::m_stateMachine->changeWeapon(WEAPON::STANDARD);

	if (Globals::m_uiManager->isKeyDown(GLFW_KEY_2))
		Globals::m_stateMachine->changeWeapon(WEAPON::WEAPON1);

	if (Globals::m_uiManager->isKeyDown(GLFW_KEY_3))
		Globals::m_stateMachine->changeWeapon(WEAPON::WEAPON2);
	
	if (Globals::m_uiManager->isKeyDown(GLFW_KEY_4))
		Globals::m_stateMachine->changeWeapon(WEAPON::WEAPON3);

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

	checkBounds();

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


	//check shoot rate
	//Again, these numbers are subject to change
	int current_score = Globals::m_stateMachine->p_score;
	if (current_score < 5000) 
	{
		Globals::m_stateMachine->upgradeWeapon(1);
	}
	else if (current_score > 5000 && current_score < 10000)
	{
		Globals::m_stateMachine->upgradeWeapon(2);
	} 
	else if (current_score > 10000 && current_score < 20000)
	{
		Globals::m_stateMachine->upgradeWeapon(3);
	}
	else
	{
		Globals::m_stateMachine->upgradeWeapon(4);
	}


	int weaponLvl = Globals::m_stateMachine->getPlayerWeaponLVL();
	//std::cout << "WEAPON LEVEL: " << weaponLvl << std::endl;
	if (weaponLvl == 1) 
	{
		m_shootRate = 0.5f;
	}
	else if (weaponLvl == 2) 
	{
		m_shootRate = 0.25f;
	}
	else if (weaponLvl == 3)
	{
		m_shootRate = 0.1f;
	}
	else if (weaponLvl == 4)
	{
		m_shootRate = 0.1f;
		m_shootRadial = true;
	}
	else 
	{
		m_shootRate = 0.5f;
	}

	m_shootTimer->setInterval(m_shootRate);

	// Auto shoot
	if (m_shootTimer->checkInterval())
	{
		shoot();
	}

	changeColor();

	return true;
}

bool Player::checkBounds()
{
	bool inBounds = true;
	glm::vec3 translation = m_physics->m_translation;

	if (translation.x < ShmupGame::WORLD_LOWER_BOUND_X)
	{
		inBounds = false;
		m_physics->setTranslation(glm::vec3(ShmupGame::WORLD_LOWER_BOUND_X, translation.y, translation.z));
		//m_physics->setVelocity(0.0, 0.0);
	}
	else if (translation.x > ShmupGame::WORLD_UPPER_BOUND_X)
	{
		inBounds = false;
		m_physics->setTranslation(glm::vec3(ShmupGame::WORLD_UPPER_BOUND_X, translation.y, translation.z));
	}

	if (translation.y < ShmupGame::WORLD_LOWER_BOUND_Y)
	{
		inBounds = false;
		m_physics->setTranslation(glm::vec3(translation.x, ShmupGame::WORLD_LOWER_BOUND_Y, translation.z));
	}
	else if (translation.y > ShmupGame::WORLD_UPPER_BOUND_Y)
	{
		inBounds = false;
		m_physics->setTranslation(glm::vec3(translation.x, ShmupGame::WORLD_UPPER_BOUND_Y, translation.z));
	}

	return false;
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
		bullet->collide();

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

	//bullet velocities
	float b2x, b3x;

	//bullet spread; based on velocity vector
	switch (Globals::m_stateMachine->getPlayerWeapon()) {
	case WEAPON::STANDARD:
		b2x = -1.0f;
		b3x = 1.0f;
		break;
	case WEAPON::WEAPON1:
		b2x = -2.0f;
		b3x = 2.0;
		break;
	case WEAPON::WEAPON2:
		b2x = -3.0f;
		b3x = 3.0f;
		break;
	case WEAPON::WEAPON3:
		b2x = -4.0f;
		b3x = 4.0f;
		break;
	default:
		b2x = -1.0f;
		b3x = 1.0f;
	}
	//3 bullet streams

	m_shootComponent->shoot(pos.x, pos.y, vx, vy);
	m_shootComponent->shoot(pos.x, pos.y, b2x, vy);
	m_shootComponent->shoot(pos.x, pos.y, b3x, vy);

	//radial shoot
	if (m_shootRadial) {
		m_shootComponent->shootRadial(pos.x, pos.y, 4.0f, 6);
	}
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
	for (uint i = 0; i < m_minionCount - oldMinionCount; i++)
	{
		float x = glm::linearRand(-2.0f, 2.0f);
		float y = glm::linearRand(-2.0f, 0.0f);
		Minion* newMinion = new Minion(b2Vec2(x, y));
	}
}