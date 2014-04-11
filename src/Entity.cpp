#include "Entity.h"

#include <glm/gtx/string_cast.hpp>
#include "Globals.h"
#include "GameManager.h"
#include "DataManager.h"
#include "RenderManager.h"
#include "ShaderCommon.h"
#include "Mesh.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"

Entity::Entity(Entity* parent) :
    m_render(0),
    m_physics(0),
	m_dead(false)
{
    m_parent = parent == 0 ? Globals::m_gameManager->m_rootEntity : parent;
    if (m_parent != 0) m_parent->m_children.push_back(this);

    m_transform = new Transform(this);

    Globals::m_gameManager->addEntity(this);
}

Entity::~Entity()
{
	
}

void Entity::destroy()
{
	// Object removed and marked for deletion. Deletion happens inside GameManager update loop.
	m_dead = true;
	if (m_parent != 0) m_parent->m_children.remove(this); // Remove from parent's list
	Globals::m_gameManager->removeEntity(this);

	// Delete components
	while (m_components.size() > 0)
	{
		delete m_components.front();
	}

	while (m_children.size() > 0)
	{
		m_children.front()->destroy();
	}

}

void Entity::update()
{
    // Concat parent's matrix to get render matrix
    m_transform->update();
    m_renderMatrix = m_transform->m_matrix;
    if (m_parent != 0)
    {
        m_renderMatrix = m_parent->m_renderMatrix * m_renderMatrix;
    }
} 

void Entity::render()
{
    if (!m_render) return;

    ShaderCommon::TransformGL transform;
    transform.modelMatrix = m_renderMatrix;
    Globals::m_renderManager->renderTransform(transform);

    m_render->render();
}

glm::vec3 Entity::getPosition()
{
    return glm::vec3(m_renderMatrix[3]);
}

void Entity::onCollisionEnter(Entity* collider)
{
    //printf("collision enter");
}

void Entity::onCollisionLeave(Entity* collider)
{
    //printf("collision leave");
}