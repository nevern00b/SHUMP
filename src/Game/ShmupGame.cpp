#include "ShmupGame.h"

#include "Globals.h"
#include "DataManager.h"
#include "Rendering/RenderManager.h"
#include "UIManager.h"
#include "Common.h"
#include "Entity.h"
#include "Light.h"
#include "Camera.h"
#include "Transform.h"
#include "Rendering/Material.h"
#include "Utils.h"
#include "Physics/PhysicsComponent.h"
#include "Entity.h"
#include "Physics/PhysicsManager.h"
#include "Rendering/RenderComponent.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

const float ShmupGame::WORLD_BOUND_X = 16.0f;
const float ShmupGame::WORLD_BOUND_Y = 9.0f;

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

	Mesh* mesh = Globals::m_dataManager->getMesh("cube");
	Material* material = Globals::m_dataManager->getMaterial("yellow");
	b2PolygonShape shape;
	shape.SetAsBox(0.05f, 0.05f);
	PhysicsData physicsData(shape, 0, 0);
	m_playerBulletPool = new BulletPool(100, mesh, material, physicsData);

    Player* player = new Player();
	Enemy* enemy = new Enemy();

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

