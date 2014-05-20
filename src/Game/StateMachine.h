//Header File for the State Machine
#pragma once

enum COLOR
{
	STATIC,
	RED,
	BLUE,
	GREEN,
	YELLOW
};

enum WEAPON{
	STANDARD,
	WEAPON1,
	WEAPON2,
	WEAPON3,

};


class StateMachine{
public:
	void checkStates();

	COLOR getPlayerState();
	int getPlayerWeapon();
	int getPlayerWeaponLVL();

	void changePlayerState(COLOR input);
	void changeWeapon(WEAPON input);
	void upgradeWeapon(int level);
	void resetWeapon();
	void addScore(int input);

	int p_score = 0;

private:
	//Player Attributes
	COLOR p_state = COLOR::RED;
	WEAPON p_weapon = WEAPON::STANDARD;
	int p_weaponLVL = 1;
	
};