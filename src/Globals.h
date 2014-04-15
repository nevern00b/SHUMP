#pragma once

class UIManager;
class RenderManager;
class DataManager;
class ShmupGame;
class PhysicsManager;
class StateMachine;

class Globals
{

public:

    static void init();
	static void destroy();

    static RenderManager* m_renderManager;
    static UIManager* m_uiManager;
    static DataManager* m_dataManager;
    static ShmupGame* m_shmupGame;
    static PhysicsManager* m_physicsManager;
	static StateMachine* m_stateMachine;

};
