#include "RenderComponent.h"

#include "Entity.h"
#include "Globals.h"
#include "RenderManager.h"
#include "GameManager.h"
#include "Mesh.h"

RenderComponent::RenderComponent(Entity* entity, Mesh* mesh, Material* material) : Component(entity),
    m_mesh(mesh),
    m_materials(1, material)
{
    m_entity->m_render = this;
    Globals::m_renderManager->addEntity(m_entity);
}

RenderComponent::~RenderComponent()
{
    Globals::m_renderManager->removeEntity(m_entity);
}

void RenderComponent::render()
{
    m_mesh->render(m_materials);
}

void RenderComponent::setMaterial(Material* material)
{
	// TO-DO: need to update RenderManager with the material change in case the material is of a different shader
	m_materials[0] = material;
}