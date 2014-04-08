#include "GameManager.h"

#include <algorithm>
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

GameManager::GameManager() :
    m_camera(0),
    m_rootEntity(0)
{
    // Don't put anything here
}

GameManager::~GameManager()
{

}

void GameManager::init()
{
    m_rootEntity = new Entity(0, 0, Transform());
    m_rootEntity->m_name = "Root";

    // Create cube
    Material* cubeMaterial = new Material();
    cubeMaterial->m_diffuseColor = glm::vec4(1, 0, 0, 1);
    b2Shape* cubeShape = Utils::createBoxShape(1.0f, 1.0f);
    PhysicsData* cubePhysics = new PhysicsData(cubeShape, 1.0f, 0.2f, 0.5f);
    
    EntityData cubeData;
    cubeData.m_mesh = Globals::m_dataManager->getMesh("cube");
    cubeData.m_materials.push_back(cubeMaterial);
    cubeData.m_physics = cubePhysics;

    Entity* cube = new Entity(0, &cubeData, Transform(glm::vec3(0,5,0)));

    // Create floor
    PhysicsData* floorPhysics = new PhysicsData(cubeShape, 1.0f, 0.2f, 0.5f);
    floorPhysics->m_bodyType = b2_staticBody;

    EntityData floorData;
    floorData.m_mesh = Globals::m_dataManager->getMesh("cube");
    floorData.m_materials.push_back(cubeMaterial);
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

void GameManager::update()
{
    m_rootEntity->update(); // Update objects in scene graph order
}

Entity* GameManager::getEntity(const std::string& name)
{
    for (auto& entity : m_entities)
    {
        if (entity->m_name == name)
        {
            return entity;
        }
    }

    return 0;
}

void GameManager::addEntity(Entity* entity)
{
    m_entities.push_back(entity);

    // If the entity is renderable, send it to the render manager
    if (entity->m_mesh != 0)
    {
        Globals::m_renderManager->addEntity(entity);
    }
}

void GameManager::addDirLight(DirLight* dirLight)
{
    m_dirLights.push_back(dirLight);
    Globals::m_renderManager->m_lightBufferDirty = true;
}

void GameManager::addPointLight(PointLight* pointLight)
{
    m_pointLights.push_back(pointLight);
    Globals::m_renderManager->m_lightBufferDirty = true;
}

void GameManager::setCamera(Camera* camera)
{
    m_camera = camera;
}

void GameManager::removeEntity(Entity* entity)
{
    m_entities.remove(entity);

    // If the entity is renderable, send it to the render manager
    if (entity->m_mesh != 0)
    {
        Globals::m_renderManager->removeEntity(entity);
    }
}

void GameManager::removeDirLight(DirLight* dirLight)
{
    m_dirLights.remove(dirLight);
}

void GameManager::removePointLight(PointLight* pointLight)
{
    m_pointLights.remove(pointLight);
}
