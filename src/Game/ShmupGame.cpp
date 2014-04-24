#include "ShmupGame.h"

#include <glm/gtc/noise.hpp>
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
#include "EnemyManager.h"
#include "BulletPool.h"
#include "Rendering/ParticleSystem.h"
#include "Rendering/Mesh.h"
#include "Floor.h"
#include "Item.h"

const float ShmupGame::WORLD_BOUND_X = 16.0f;
const float ShmupGame::WORLD_BOUND_Y = 12.0f;

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



	// Test out noise
	const uint noiseSize = 256;

	uchar data[noiseSize*noiseSize*3];
	for (uint y = 0; y < noiseSize; y++)
	for (uint x = 0; x < noiseSize; x++)
	{
		float value = glm::simplex(glm::vec2(x / 16.f, y / 16.f));
		uchar color = (uchar)((value * 0.5f + 0.5f) * 255);
		uint index = (x + noiseSize * y) * 3;
		data[index+0] = color; // R
		data[index+1] = color; // G
		data[index+2] = color; // B
	}
	Globals::m_dataManager->loadTexture(data, glm::uvec2(noiseSize, noiseSize), "noise");


	// Create bullet pools
	Mesh* sphereMesh = Globals::m_dataManager->getMesh("sphere");
	Mesh* mesh = Globals::m_dataManager->getMesh("cube");
	b2PolygonShape shape;
	shape.SetAsBox(0.05f, 0.05f);
	PhysicsData physicsData(shape);
	physicsData.m_groupIndex = ShmupGame::PLAYER_GROUP;
	
	Material* yellowMaterial = Globals::m_dataManager->getMaterial("yellow");
	m_yellowBulletPool = new BulletPool(50, sphereMesh, yellowMaterial, physicsData, COLOR::YELLOW);
	
	Material* redMaterial = Globals::m_dataManager->getMaterial("red");
	m_redBulletPool = new BulletPool(50, sphereMesh, redMaterial, physicsData, COLOR::RED);
	
	Material* greenMaterial = Globals::m_dataManager->getMaterial("green");
	m_greenBulletPool = new BulletPool(50, sphereMesh, greenMaterial, physicsData, COLOR::GREEN);
	
	Material* blueMaterial = Globals::m_dataManager->getMaterial("blue");
	m_blueBulletPool = new BulletPool(50, sphereMesh, blueMaterial, physicsData, COLOR::BLUE);
	
	physicsData.m_groupIndex = ShmupGame::ENEMY_GROUP;
	m_enemyRBulletPool = new BulletPool(50, sphereMesh, redMaterial, physicsData, COLOR::RED);

	physicsData.m_groupIndex = ShmupGame::ENEMY_GROUP;
	m_enemyBBulletPool = new BulletPool(50, sphereMesh, blueMaterial, physicsData, COLOR::BLUE);

	physicsData.m_groupIndex = ShmupGame::ENEMY_GROUP;
	m_enemyGBulletPool = new BulletPool(50, sphereMesh, greenMaterial, physicsData, COLOR::GREEN);
	
	physicsData.m_groupIndex = ShmupGame::ENEMY_GROUP;
	m_enemyYBulletPool = new BulletPool(50, sphereMesh, yellowMaterial, physicsData, COLOR::YELLOW);
	
	
	// Create particle system
	m_particleSystem = new ParticleSystem(100, mesh, yellowMaterial);
	
	m_player = new Player();
	m_player->m_transform->setTranslation(-2, -5);

	m_enemyManager = new EnemyManager();

	// Create floor
	Floor* floor = new Floor();

	// Item
	Item* item = new ImmunityItem(COLOR::YELLOW, 0.0f, -5.0f);

    // Create lights
    PointLight* light = new PointLight(0, glm::vec3(1, 1, 1), 40);
    light->m_transform->setTranslation(glm::vec3(5, 10, 0));
	
    DirLight* dirlight = new DirLight(0, glm::vec3(1, 1, 1));
    dirlight->m_transform->rotate(30, glm::vec3(1, 0, 0));
	
    Camera* camera = new Camera(0, 45.0f);
	//camera->setPan(0, 5);
    //camera->setZoom(20);
	camera->setRotation(0, 70.0f);
	camera->setPan(0.0f, -17.15f);
	camera->setZoom(20.0f);
}

void ShmupGame::update()
{
	m_enemyManager->update();

	if (Globals::m_uiManager->isKeyDown(GLFW_KEY_GRAVE_ACCENT))
	{
		m_player->gainLives(100);
	}

	GameManager::update();
	//printf("===================");
	//printf("Camera angleX: %f angleY: %f trans: %f %f %f\n", m_camera->m_angleHorizontal, m_camera->m_angleVertical, m_camera->m_transform->m_translation.x, m_camera->m_transform->m_translation.y, m_camera->m_transform->m_translation.z);
}
