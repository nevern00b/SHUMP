#include "ShmupGame.h"

#include "Globals.h"
#include "DataManager.h"
#include "RenderManager.h"
#include "UIManager.h"
#include "Common.h"
#include "Entity.h"
#include "Light.h"
#include "Camera.h"
#include "Transform.h"
#include "Material.h"
#include "Utils.h"
#include "PhysicsComponent.h"
#include "Entity.h"
#include "PhysicsManager.h"
#include "RenderComponent.h"
#include "Player.h"

const float ShmupGame::WORLD_BOUND_X = 10.0f;
const float ShmupGame::WORLD_BOUND_Y = 10.0f;

ShmupGame::ShmupGame() : GameManager()
{
    
}

ShmupGame::~ShmupGame()
{
	// TO-DO: delete player here?
}

void ShmupGame::init()
{
    GameManager::init();

    Player* player = new Player();

    // Create floor

	Material* material = Globals::m_dataManager->getMaterial("red");
	Mesh* mesh = Globals::m_dataManager->getMesh("cube");
	b2Shape* shape = Globals::m_physicsManager->m_squareBig;
	PhysicsData physicsData(shape, 0, 0);
	Entity* wall = new Entity(0);
	PhysicsComponent* physics = new PhysicsComponent(wall, physicsData);
	RenderComponent* render = new RenderComponent(wall, mesh, { material });

    // Create lights
    PointLight* light = new PointLight(0, glm::vec3(1, 1, 1), 40);
    light->m_transform->setTranslation(glm::vec3(5, 10, 0));

    DirLight* dirlight = new DirLight(0, glm::vec3(1, 1, 1));
    dirlight->m_transform->rotate(90, glm::vec3(1, 0, 0));

    Camera* camera = new Camera(0, 45.0f);
    camera->setZoom(20);
}

void ShmupGame::update()
{
    GameManager::update();
}