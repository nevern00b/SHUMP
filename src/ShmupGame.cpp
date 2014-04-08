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

    // Create player
    
    
    b2Shape* cubeShape = Utils::createBoxShape(1.0f, 1.0f);
    PhysicsData* cubePhysics = new PhysicsData(cubeShape, 1.0f, 0.2f, 0.5f);

    EntityData cubeData;
    cubeData.m_mesh = Globals::m_dataManager->getMesh("cube");
    cubeData.m_materials.push_back(greenMaterial);
    cubeData.m_physics = cubePhysics;

    m_player = new Entity(0, &cubeData, Transform(glm::vec3(0, 5, 0)));

    // Create floor
    PhysicsData* floorPhysics = new PhysicsData(cubeShape, 1.0f, 0.2f, 0.5f);
    floorPhysics->m_bodyType = b2_staticBody;

    EntityData floorData;
    floorData.m_mesh = Globals::m_dataManager->getMesh("cube");
    floorData.m_materials.push_back(redMaterial);
    floorData.m_physics = floorPhysics;

    Entity* floor = new Entity(0, &floorData, Transform(glm::vec3(0, 0, 0)));

    // Create lights
    PointLight* light = new PointLight(0, new LightData(glm::vec3(1, 1, 1), 40), Transform(glm::vec3(5, 10, 0)));
    DirLight* dirlight = new DirLight(0, new LightData(glm::vec3(1, 1, 1), 0), Transform());
    dirlight->m_transform->rotate(90, glm::vec3(1, 0, 0));

    CameraData cameraData(45.0f);
    Camera* camera = new Camera(0, &cameraData, Transform());
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