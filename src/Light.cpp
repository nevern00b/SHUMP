#include "Light.h"

#include "Globals.h"
#include "DataManager.h"
#include "Rendering/Material.h"
#include "Game/ShmupGame.h"

Light::Light(Entity* parent, const glm::vec3& color) : Entity(parent),
    m_color(color)
{
    
}

Light::~Light()
{

}



DirLight::DirLight(Entity* parent, const glm::vec3& color) : Light(parent, color)
{
    Globals::m_shmupGame->addDirLight(this);
}

DirLight::~DirLight()
{
    Globals::m_shmupGame->removeDirLight(this);
}

glm::vec3 DirLight::getDirection()
{
    return m_transform->getForwardVector();
}

PointLight::PointLight(Entity* parent, const glm::vec3& color, float radius) : Light(parent, color),
    m_radius(radius)
{
    Globals::m_shmupGame->addPointLight(this);
}

PointLight::~PointLight()
{
    Globals::m_shmupGame->removePointLight(this);
}
