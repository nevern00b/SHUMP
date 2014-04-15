#include "GameManager.h"

#include <algorithm>
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

GameManager::GameManager() :
    m_camera(0),
    m_rootEntity(0)
{
    
}

GameManager::~GameManager()
{
	// Will delete the whole scene graph
	m_rootEntity->destroy();
	destroyMarkedEntities();
}

void GameManager::init()
{
    m_rootEntity = new Entity(0);
    m_rootEntity->m_name = "Root";
}

void GameManager::update()
{
	// New objects may be added during the update loop, so only iterate up to the last element
	for (auto& it = m_entities.begin(), end = m_entities.end(); it != end; ++it) 
	{
		Entity* entity = *it;
		if (entity->m_dead) continue;
		entity->update();
	}

	destroyMarkedEntities();
}

void GameManager::destroyMarkedEntities()
{
	// Delete entities that were destroyed during the update
	for (auto& entity : m_entitiesToRemove)
	{
		m_entities.remove(entity);
		delete entity;
	}
	m_entitiesToRemove.clear();
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
	m_entitiesToRemove.push_back(entity);
}

void GameManager::removeDirLight(DirLight* dirLight)
{
    m_dirLights.remove(dirLight);
}

void GameManager::removePointLight(PointLight* pointLight)
{
    m_pointLights.remove(pointLight);
}
