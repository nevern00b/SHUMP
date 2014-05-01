//File for the State Machine
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "StateMachine.h"


void StateMachine::checkStates(){
	printf("The player state is: %d\n", p_state);
	printf("The score is: %d\n", p_score);
}

//Return Methods
COLOR StateMachine::getPlayerState()
{
	return p_state;
}

int StateMachine::getPlayerWeapon()
{
	return p_weapon;
}

int StateMachine::getPlayerWeaponLVL()
{
	return p_weaponLVL;
}


//Change Methods
void StateMachine::changePlayerState(COLOR input)
{
	p_state = input;
}

void StateMachine::changeWeapon(WEAPON input)
{
	p_weapon = input;
}

void StateMachine::upgradeWeapon()
{
	p_weaponLVL++;
}

void StateMachine::resetWeapon()
{
	p_weaponLVL = 1;
}
