#include "Globals.h"

#include "UIManager.h"
#include "DataManager.h"
#include "Physics/PhysicsManager.h"
#include "Rendering/RenderManager.h"
#include "Game/ShmupGame.h"
#include "AnimationManager.h"

RenderManager* Globals::m_renderManager;
UIManager* Globals::m_uiManager;
DataManager* Globals::m_dataManager;
ShmupGame* Globals::m_shmupGame;
PhysicsManager* Globals::m_physicsManager;
StateMachine* Globals::m_stateMachine;
AnimationManager* Globals::m_animationManager;

void Globals::init(float time, uint screenWidth, uint screenHeight)
{
	// Create all the global managers
	m_uiManager = new UIManager(time, screenWidth, screenHeight);
	m_uiManager->update(time);

	m_dataManager = new DataManager();
	m_physicsManager = new PhysicsManager();
	m_renderManager = new RenderManager();
	m_stateMachine = new StateMachine();
	m_animationManager = new AnimationManager();
	m_shmupGame = new ShmupGame();
	m_shmupGame->init();
}

void Globals::update(float time)
{	
	m_physicsManager->update();
	m_animationManager->update();
	m_shmupGame->update();
    m_uiManager->update(time);
}

void Globals::render()
{
    m_renderManager->render();
}

void Globals::destroy()
{
	delete m_uiManager;
	delete m_dataManager;
	delete m_shmupGame;
	delete m_renderManager;
	delete m_physicsManager;
	delete m_stateMachine;
	delete m_animationManager;
}