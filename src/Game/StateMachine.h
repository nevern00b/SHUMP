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
public:
	COLOR getBState();
	COLOR getIState();
	void checkStates();
	void changeBState(COLOR input);
	void changeIState(COLOR input);
private:
	COLOR bulletST = COLOR::RED;
	COLOR immunST = COLOR::RED;
};