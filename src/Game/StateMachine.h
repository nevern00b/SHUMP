//Header File for the State Machine
#pragma once
#include <iostream>
#include <utility>
#include "BulletPool.h"
#include "Globals.h"
#include "ShmupGame.h"
#include <glm/gtc/random.hpp>


class StateMachine {
public:
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
	float changeEnemySpawnRate(int score);

	//Bullet state
	BulletPool* changeBulletPool(int playerState);
	std::pair<float, float> changeBulletSpread(WEAPON wp);

	void addScore(int input);
	int p_score = 0;

private:
	//Player Attributes
	COLOR p_state = COLOR::RED;
	WEAPON p_weapon = WEAPON::STANDARD;
	int p_weaponLVL = 1;
};