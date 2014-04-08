#include "Light.h"

#include "Globals.h"
#include "GameManager.h"
#include "DataManager.h"
#include "Material.h"

Light::Light(Entity* parent, const glm::vec3& color) : Entity(parent),
    m_color(color)
{
    
}

Light::~Light()
{

}



DirLight::DirLight(Entity* parent, const glm::vec3& color) : Light(parent, color)
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

PointLight::PointLight(Entity* parent, const glm::vec3& color, float radius) : Light(parent, color),
    m_radius(radius)
{
    Globals::m_gameManager->addPointLight(this);
}

PointLight::~PointLight()
{
    Globals::m_gameManager->removePointLight(this);
}
