//File for the State Machine
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "StateMachine.h"

StateMachine::StateMachine()
{
	p_score = 0;
	p_state = COLOR::RED;
	p_weapon = WEAPON::STANDARD;
	p_weaponLVL = 1;
	m_enemyMaxThreshold = 10;
	m_enemyCounter = 0;
}

StateMachine::~StateMachine()
{

}

void StateMachine::checkStates()
{
	printf("The player state is: %d\n", p_state);
	printf("The score is: %d\n", p_score);

}

//Return Methods
COLOR StateMachine::getPlayerState()
{
	return p_state;
}

WEAPON StateMachine::getPlayerWeapon()
{
	return p_weapon;
}

int StateMachine::getPlayerWeaponLVL()
{
	return p_weaponLVL;
}


//Transition methods: Player
void StateMachine::changePlayerState(COLOR input)
{
	p_state = input;
}

void StateMachine::changeWeapon(WEAPON input)
{
	p_weapon = input;
}

void StateMachine::upgradeWeapon(int score)
{
	if (score < 5000)
	{
		p_weaponLVL = 1;
	}
	else if (score >= 5000 && score < 10000)
	{
		p_weaponLVL = 2;
	}
	else if (score >= 10000 && score < 20000)
	{
		p_weaponLVL = 3;
	}
	else if (score >= 20000 && score < 30000)
	{
		p_weaponLVL = 4;
	}
	else p_weaponLVL = 5;
}

void StateMachine::resetWeapon()
{
	p_weaponLVL = 1;
}

float StateMachine::changeShootRate()
{
	float m_shootRate;
	switch (p_weaponLVL)
	{
		case 1:
			m_shootRate = 0.5f;
			break;
		case 2:
			m_shootRate = 0.4f;
			break;
		case 3:
			m_shootRate = 0.3f;
			break;
		case 4:
			m_shootRate = 0.2f;
			break;
		case 5:
			m_shootRate = 0.1f;
			break;
		default:
			m_shootRate = 0.5f;
	}
		///m_shootRadial = true;
	return m_shootRate;
}

//Transition methods: Enemy
float StateMachine::changeEnemySpawnRate(int score)
{
	float spawn_rate = 3.00f;
	if (score < 1500)
	{
		spawn_rate = 3.00f;
	}
	else if (score > 1500 && score < 2000)
	{
		spawn_rate = 2.75f;
	}
	else if (score > 2000 && score < 3000)
	{
		spawn_rate = 2.50f;
	}
	else if (score > 3000 && score < 6000)
	{
		spawn_rate = 2.25f;
	}
	else if (score > 6000 && score < 15000)
	{
		spawn_rate = 2.00f;
	}
	else if (score > 15000 && score < 18000)
	{
		spawn_rate = 1.50f;
	}
	else
	{
		spawn_rate = 1.00f;
	}
	std::cout << "spawn rate is: " << spawn_rate << std::endl;
	return spawn_rate;
}

//Transition methods: Bullet
BulletPool* StateMachine::changeBulletPool(int playerState)
{
	BulletPool* finalPool = Globals::m_shmupGame->m_redBulletPool;
	if (playerState == COLOR::RED)
	{
		finalPool = Globals::m_shmupGame->m_redBulletPool;
	}
	else if (playerState == COLOR::BLUE)
	{
		finalPool = Globals::m_shmupGame->m_blueBulletPool;
	}
	else if (playerState == COLOR::GREEN)
	{
		finalPool = Globals::m_shmupGame->m_greenBulletPool;
	}
	else if (playerState == COLOR::YELLOW)
	{
		finalPool = Globals::m_shmupGame->m_yellowBulletPool;
	}
	return finalPool;
}

std::pair<float, float> StateMachine::changeBulletSpread(WEAPON wp)
{
	float b2x, b3x;
	switch (wp) {
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
	std::pair<float, float> vel(b2x, b3x);
	return vel;
}


void StateMachine::incEnemy(int amt)
{
	m_enemyCounter = std::min(m_enemyCounter + amt, m_enemyMaxThreshold);
}

void StateMachine::decEnemy()
{
	m_enemyCounter = std::max(m_enemyCounter - 1, 0);
}