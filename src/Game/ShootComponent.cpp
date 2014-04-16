#include "ShootComponent.h"

#include <glm/gtc/constants.hpp>
#include "BulletPool.h"

ShootComponent::ShootComponent(Entity* entity, BulletPool* bulletPool) : Component(entity),
	m_bulletPool(bulletPool)
{
	
}

ShootComponent::~ShootComponent()
{

}

void ShootComponent::shoot(float x, float y, float vx, float vy)
{
	m_bulletPool->create(x, y, vx, vy);
}

void ShootComponent::shootRadial(float x, float y, float speed, uint count)
{
	for (uint i = 0; i < count; i++)
	{
		float angle = 2 * 3.14f * ((float)i / count);
		float vx = glm::cos(angle) * speed;
		float vy = glm::sin(angle) * speed;

		m_bulletPool->create(x, y, vx, vy);
	}
}