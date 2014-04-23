#include "Entity.h"

#include <glm/gtx/string_cast.hpp>
#include "Globals.h"
#include "GameManager.h"
#include "DataManager.h"
#include "Rendering/RenderManager.h"
#include "Rendering/ShaderCommon.h"
#include "Rendering/Mesh.h"
#include "Physics/PhysicsComponent.h"
#include "Rendering/RenderComponent.h"
#include "Game/ShmupGame.h"

Entity::Entity(Entity* parent) : EventObject(),
    m_render(0),
    m_physics(0),
	m_dead(false),
	m_parent(0)
{
	setParent(parent);

    m_transform = new Transform(this);

    Globals::m_shmupGame->addEntity(this);
}

Entity::~Entity()
{
	
}

void Entity::destroy()
{
	// Object removed and marked for deletion. Deletion happens inside GameManager update loop.
	m_dead = true;
	if (m_parent != 0) m_parent->m_children.remove(this); // Remove from parent's list
	Globals::m_shmupGame->removeEntity(this);

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

void Entity::setParent(Entity* parent)
{
	//TO-DO: scene graph transform won't work if new parent was created after this entity. Need to re-order entity list
	
	// Remove from previous parent
	if (m_parent != 0)
	{
		m_parent->m_children.remove(this);
	}

	m_parent = parent == 0 ? Globals::m_shmupGame->m_rootEntity : parent;
	if (m_parent != 0) m_parent->m_children.push_back(this);
}

void Entity::update()
{
    // Concat parent's matrix to get render matrix
    m_transform->update();
    m_renderMatrix = m_transform->m_matrix;

	// Do not concatenate parent matrix if there is no parent or the parent is the root
    if (m_parent != 0 && m_parent->m_parent != 0)
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

void Entity::onCollisionEnter(EventObject* collider)
{
    //printf("collision enter");
}

void Entity::onCollisionLeave(EventObject* collider)
{
    //printf("collision leave");
}