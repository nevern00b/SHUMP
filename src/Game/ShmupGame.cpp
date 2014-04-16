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
#include "BulletPool.h"

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
	b2PolygonShape shape;
	shape.SetAsBox(0.05f, 0.05f);
	PhysicsData physicsData(shape);
	physicsData.m_groupIndex = ShmupGame::PLAYER_GROUP;

	Material* yellowMaterial = Globals::m_dataManager->getMaterial("yellow");
	m_yellowBulletPool = new BulletPool(200, mesh, yellowMaterial, physicsData);

	Material* redMaterial = Globals::m_dataManager->getMaterial("red");
	m_redBulletPool = new BulletPool(200, mesh, redMaterial, physicsData);

	Material* greenMaterial = Globals::m_dataManager->getMaterial("green");
	m_greenBulletPool = new BulletPool(200, mesh, greenMaterial, physicsData);

	Material* blueMaterial = Globals::m_dataManager->getMaterial("blue");
	m_blueBulletPool = new BulletPool(200, mesh, blueMaterial, physicsData);

	physicsData.m_groupIndex = ShmupGame::ENEMY_GROUP;
	m_enemyBulletPool = new BulletPool(30, mesh, redMaterial, physicsData);


	Player* player = new Player();
	player->m_transform->setTranslation(-2, -5);

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
