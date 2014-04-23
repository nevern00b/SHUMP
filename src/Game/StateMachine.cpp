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

COLOR StateMachine::getBState()
{
	return bulletST;
}

COLOR StateMachine::getIState()
{
	return immunST;
}

void StateMachine::changeBState(COLOR input)
{
	bulletST = input;
}

void StateMachine::changeIState(COLOR input){
	immunST = input;
}