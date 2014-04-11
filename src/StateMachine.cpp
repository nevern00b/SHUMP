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
		bulletST = RED_ST;
		break;
	case 2:
		bulletST = BLUE_ST;
		break;
	case 3:
		bulletST = GRN_ST;
		break;
	case 4:
		bulletST = YLLW_ST;
		break;
	default:
		bulletST = bulletST;

	}
}

void StateMachine::changeIState(int input){
	switch (input){
	case 1:
		immunST = RED_ST;
		break;
	case 2:
		immunST = BLUE_ST;
		break;
	case 3:
		immunST = GRN_ST;
		break;
	case 4:
		immunST = YLLW_ST;
		break;
	default:
		immunST = immunST;

	}
}