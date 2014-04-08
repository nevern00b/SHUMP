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

ShmupGame::ShmupGame() : GameManager()
{
    
}

ShmupGame::~ShmupGame()
{

}

void ShmupGame::init()
{
    GameManager::init();

    Material* redMaterial = new Material();
    redMaterial->m_diffuseColor = glm::vec4(1, 0, 0, 1);

    Material* greenMaterial = new Material();
    greenMaterial->m_diffuseColor = glm::vec4(0, 1, 0, 1);

    b2Shape* cubeShape = Utils::createBoxShape(1.0f, 1.0f);
    Mesh* cubeMesh = Globals::m_dataManager->getMesh("cube");

    // Create player
    m_player = new Entity(0);

    PhysicsData* playerPhysicsData = new PhysicsData(cubeShape, 1.0f, 0.2f, 0.5f);
    PhysicsComponent* playerPhysics = new PhysicsComponent(m_player, playerPhysicsData);

    std::vector<Material*> playerMaterials = {greenMaterial};
    RenderComponent* playerRender = new RenderComponent(m_player, cubeMesh, playerMaterials);

    m_player->m_transform->setTranslation(0, 5);


    // Create floor

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

    float speed = 10.0f;
    b2Body* body = m_player->m_physics->m_body;

    b2Vec2 vel = body->GetLinearVelocity();
    b2Vec2 desiredVel(0,0);

    // Get keyboard input
    if (Globals::m_uiManager->isKeyDown(GLFW_KEY_A))
        desiredVel.x -= speed;
    if (Globals::m_uiManager->isKeyDown(GLFW_KEY_D))
        desiredVel.x += speed;
    if (Globals::m_uiManager->isKeyDown(GLFW_KEY_W))
        desiredVel.y += speed;
    if (Globals::m_uiManager->isKeyDown(GLFW_KEY_S))
        desiredVel.y -= speed;


    b2Vec2 velChange = desiredVel - vel;
    b2Vec2 impulse = body->GetMass() * velChange;
    body->ApplyLinearImpulse(impulse, body->GetWorldCenter(),true);
}