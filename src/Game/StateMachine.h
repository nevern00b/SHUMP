//Header File for the State Machine
#pragma once
#include <iostream>
#include <utility>
#include "BulletPool.h"
#include "Globals.h"
#include "ShmupGame.h"
#include <glm/gtc/random.hpp>
#include <cmath>

//Make state machine more or less "state-ful"?
class StateMachine {
public:
	StateMachine();
	~StateMachine();

	void checkStates();
	COLOR getPlayerState();
	WEAPON getPlayerWeapon();
	int getPlayerWeaponLVL();

	//Player state
	void changePlayerState(COLOR input);
	void changeWeapon(WEAPON input);
	void upgradeWeapon(int score);
	void resetWeapon();
	float changeShootRate();

	//Enemy state
	//Move this elsewhere?
	float changeEnemySpawnRate(int score);
	void incEnemy(int amt);
	void decEnemy();

	//Bullet state
	BulletPool* changeBulletPool(int playerState);
	std::pair<float, float> changeBulletSpread(WEAPON wp);

	void addScore(int input);
	int p_score;
	uint m_lives;

	// Make these private after testing...
	int m_enemyMaxThreshold;
	int m_enemyCounter;

private:
	// Player Attributes
	COLOR p_state;
	WEAPON p_weapon;
	int p_weaponLVL;

};