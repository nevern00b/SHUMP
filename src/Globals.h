#pragma once

#include "Common.h"

class UIManager;
class RenderManager;
class DataManager;
class ShmupGame;
class PhysicsManager;
class StateMachine;
class AnimationManager;

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

class Globals
{

public:

	static void init(float time, uint screenWidth, uint screenHeight);
	static void destroy();
	static void update(float time);
    static void render();

    static RenderManager* m_renderManager;
    static UIManager* m_uiManager;
    static DataManager* m_dataManager;
    static ShmupGame* m_shmupGame;
    static PhysicsManager* m_physicsManager;
	static StateMachine* m_stateMachine;
	static AnimationManager* m_animationManager;
};
