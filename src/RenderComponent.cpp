#include "RenderComponent.h"

#include "Entity.h"
#include "Globals.h"
#include "RenderManager.h"
#include "GameManager.h"
#include "Mesh.h"

RenderComponent::RenderComponent(Entity* entity, Mesh* mesh, const std::vector<Material*>& materials) : Component(entity),
    m_mesh(mesh),
    m_materials(materials)
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
