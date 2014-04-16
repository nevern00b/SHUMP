//File for the State Machine
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "StateMachine.h"


void StateMachine::checkStates(){
	printf("The Bullet State is: %d \n", bulletST);
	printf("The Immunity State is: %d \n", immunST);
}

int StateMachine::getBState(){
	return bulletST;
}

int StateMachine::getIState(){
	return immunST;
}

void StateMachine::changeBState(int input){
	switch (input){
	case 1:
		bulletST = COLOR::RED;
		break;
	case 2:
		bulletST = COLOR::BLUE;
		break;
	case 3:
		bulletST = COLOR::GREEN;
		break;
	case 4:
		bulletST = COLOR::YELLOW;
		break;
	default:
		bulletST = bulletST;

	}
}

void StateMachine::changeIState(int input){
	switch (input){
	case 1:
		immunST = COLOR::RED;
		break;
	case 2:
		immunST = COLOR::BLUE;
		break;
	case 3:
		immunST = COLOR::GREEN;
		break;
	case 4:
		immunST = COLOR::YELLOW;
		break;
	default:
		immunST = immunST;

	}
}