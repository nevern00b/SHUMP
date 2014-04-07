#include "Light.h"

#include "Globals.h"
#include "GameManager.h"
#include "DataManager.h"
#include "Material.h"

Light::Light(Entity* parent, LightData* data, const Transform& transform) : Entity(parent, data, transform),
    m_color(data->m_color)
{
    
}

Light::~Light()
{

}



DirLight::DirLight(Entity* parent, LightData* data, const Transform& transform) : Light(parent, data, transform)
{
    Globals::m_gameManager->addDirLight(this);
}

DirLight::~DirLight()
{
    Globals::m_gameManager->removeDirLight(this);
}

glm::vec3 DirLight::getDirection()
{
    return m_transform->getForwardVector();
}

PointLight::PointLight(Entity* parent, LightData* data, const Transform& transform) : Light(parent, data, transform),
    m_radius(data->m_radius)
{
    Globals::m_gameManager->addPointLight(this);
}

PointLight::~PointLight()
{
    Globals::m_gameManager->removePointLight(this);
}

LightData::LightData(const glm::vec3& color, float radius) : EntityData(),
    m_color(color),
    m_radius(radius)
{

}

LightData::~LightData()
{

}