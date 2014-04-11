#pragma once

class UIManager;
class RenderManager;
class DataManager;
class GameManager;
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
    static GameManager* m_gameManager;
    static PhysicsManager* m_physicsManager;
	static StateMachine* m_stateMachine;

};
