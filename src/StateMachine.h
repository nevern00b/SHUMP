//Header File for the State Machine
#pragma once

#define STATIC_ST 0;
#define RED_ST 1;
#define BLUE_ST 2;
#define GRN_ST 3;
#define YLLW_ST 4;

class StateMachine{
	int bulletST = RED_ST;
	int immunST = STATIC_ST;
public:
	int getBState();
	int getIState();
	void checkStates();
	void changeBState(int input);
	void changeIState(int input);
};