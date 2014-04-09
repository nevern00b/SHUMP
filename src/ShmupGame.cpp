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

ShmupGame::ShmupGame() : GameManager()
{
    
}

ShmupGame::~ShmupGame()
{

}

void ShmupGame::init()
{
    GameManager::init();

    Player* player = new Player();

    // Create floor
    Material* redMaterial = new Material();
    redMaterial->m_diffuseColor = glm::vec4(1, 0, 0, 1);

    b2Shape* cubeShape = Utils::createBoxShape(1.0f, 1.0f);
    Mesh* cubeMesh = Globals::m_dataManager->getMesh("cube");

    Entity* floor = new Entity(0);

    PhysicsData* floorPhysicsData = new PhysicsData(cubeShape, 1.0f, 0.2f, 0.5f);
    floorPhysicsData->m_bodyType = b2_staticBody;
    PhysicsComponent* floorPhysics = new PhysicsComponent(floor, floorPhysicsData);

    std::vector<Material*> floorMaterials = { redMaterial };
    RenderComponent* floorRender = new RenderComponent(floor, cubeMesh, floorMaterials);
    

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