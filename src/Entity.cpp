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
#include "AnimationManager.h"

Entity::Entity(Entity* parent) : EventObject(),
    m_render(0),
    m_physics(0),
	m_dead(false),
	m_parent(0),
	m_collider(0)
{
	setParent(parent);

    m_transform = new Transform(this);

    Globals::m_shmupGame->addEntity(this);
}

Entity::~Entity()
{
	for (auto& child : m_children)
	{
		child->m_parent = 0;
	}

	if (m_parent != 0) m_parent->m_children.remove(this); // Remove from parent's list

	// Delete components
	while (m_components.size() > 0)
	{
		delete m_components.front();
	}

	Globals::m_animationManager->removeTarget((void*)this);
}

void Entity::destroy()
{
	// Object marked for deletion. Deletion happens inside GameManager update loop.
	m_dead = true;

	// Destroy children
	for (auto& child : m_children)
	{
		child->destroy();
	}
}

void Entity::setParent(Entity* parent)
{
	//TO-DO: scene graph transform won't work if parent was created after this entity. Need to re-order entity list
	
	// Remove from previous parent
	if (m_parent != 0)
	{
		m_parent->m_children.remove(this);
	}

	m_parent = parent == 0 ? Globals::m_shmupGame->m_rootEntity : parent;
	if (m_parent != 0) m_parent->m_children.push_back(this);
}

bool Entity::update()
{
	if (m_collider)
	{
		onCollide(m_collider);
		m_collider = 0;
		if (m_dead) return false;
	}	

    // Concat parent's matrix to get render matrix
    m_transform->update();
    m_renderMatrix = m_transform->m_matrix;

	// Do not concatenate parent matrix if there is no parent or the parent is the root
    if (m_parent != 0 && m_parent->m_parent != 0)
    {
        m_renderMatrix = m_parent->m_renderMatrix * m_renderMatrix;
    }

	return true;
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
	m_collider = collider;
}

void Entity::onCollide(EventObject* collider)
{
	// Overriden
}
