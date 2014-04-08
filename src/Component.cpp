#include "Component.h"

#include "Entity.h"

Component::Component()
{

}

Component::Component(Entity* entity) :
    m_entity(entity)
{
    m_entity->m_components.push_back(this);
}

Component::~Component()
{
    m_entity->m_components.remove(this);
}