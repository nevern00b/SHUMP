#pragma once

class UIManager;
class RenderManager;
class DataManager;
class GameManager;
class PhysicsManager;

class Globals
{

public:

    static void init();

    static RenderManager* m_renderManager;
    static UIManager* m_uiManager;
    static DataManager* m_dataManager;
    static GameManager* m_gameManager;
    //static PhysicsManager* m_physicsManager;

};
