#include "Globals.h"

#include "UIManager.h"
#include "DataManager.h"
#include "Physics/PhysicsManager.h"
#include "Rendering/RenderManager.h"
#include "Game/ShmupGame.h"

RenderManager* Globals::m_renderManager;
UIManager* Globals::m_uiManager;
DataManager* Globals::m_dataManager;
ShmupGame* Globals::m_shmupGame;
PhysicsManager* Globals::m_physicsManager;
StateMachine* Globals::m_stateMachine;

void Globals::init(uint screenWidth, uint screenHeight)
{
	

	// Create all the global managers
	m_uiManager = new UIManager();
	m_uiManager->m_screenWidth = screenWidth;
	m_uiManager->m_screenHeight = screenHeight;
	m_uiManager->update(0.0f);

	m_dataManager = new DataManager();
	m_physicsManager = new PhysicsManager();
	m_renderManager = new RenderManager();
	m_stateMachine = new StateMachine();
	m_shmupGame = new ShmupGame();
	m_shmupGame->init();
}

void Globals::update(float time)
{
	// Render
	m_uiManager->update(time);
	m_renderManager->render(); // Goes first because it lets the GPU start working early.
	m_physicsManager->update();
	m_shmupGame->update();
}

void Globals::destroy()
{
	delete m_uiManager;
	delete m_dataManager;
	delete m_shmupGame;
	delete m_renderManager;
	delete m_physicsManager;
	delete m_stateMachine;
}