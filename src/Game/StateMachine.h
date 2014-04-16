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

class StateMachine{
	int bulletST = COLOR::RED;
	int immunST = COLOR::STATIC;
public:
	int getBState();
	int getIState();
	void checkStates();
	void changeBState(int input);
	void changeIState(int input);
};