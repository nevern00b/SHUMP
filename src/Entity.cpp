#include "Entity.h"

#include <glm/gtx/string_cast.hpp>
#include "Globals.h"
#include "GameManager.h"
#include "DataManager.h"
#include "RenderManager.h"
#include "ShaderCommon.h"
#include "Mesh.h"
//#include "PhysicsComponent.h"

Entity::Entity(Entity* parent, EntityData* data, const Transform& transform)
{
    m_parent = parent == 0 ? Globals::m_gameManager->m_rootEntity : parent;
    if (m_parent != 0) m_parent->m_children.push_back(this);


    m_mesh = data == 0 ? 0 : data->m_mesh;
    if (data != 0) m_materials = data->m_materials;
    //m_physics = physicsData == 0 ? 0 : new PhysicsComponent(this, physicsData, transform);
    //m_transform = m_physics == 0 ? new Transform(transform) : m_physics;
    
    m_transform = new Transform(transform);

    Globals::m_gameManager->addEntity(this);
}

Entity::~Entity()
{
    if (m_parent != 0) m_parent->m_children.remove(this); // Remove from parent's list
    Globals::m_gameManager->removeEntity(this);

    //TO-DO: does this actually work?
    for (auto& child : m_children)
    {
        delete child;
    }

}

void Entity::update()
{
    // Concat parent's matrix to get render matrix
    m_renderMatrix = m_transform->getMatrix();
    if (m_parent != 0)
    {
        m_renderMatrix = m_parent->m_renderMatrix * m_renderMatrix;
    }

    // Update children
    for (auto& child : m_children)
    {
        child->update();
    }
} 

void Entity::render()
{
    if (m_mesh == 0) return; // Don't render if there isn't a mesh

    ShaderCommon::TransformGL transform;
    transform.modelMatrix = m_renderMatrix;
    Globals::m_renderManager->renderTransform(transform);

    m_mesh->render(m_materials);
}

glm::vec3 Entity::getPosition()
{
    return glm::vec3(m_renderMatrix[3]);
}


EntityData::EntityData() : 
    m_mesh(0)
{

}