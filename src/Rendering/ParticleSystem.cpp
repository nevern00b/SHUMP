#include "ParticleSystem.h"

#include <glm/gtc/random.hpp>
#include "Game/ShmupGame.h"
#include "Globals.h"
#include "UIManager.h"

ParticleSystem::ParticleSystem(uint size, Mesh* mesh, Material* material) : ObjectPool(size, mesh, material)
{
	for (uint i = 0; i < m_size; i++)
	{
		m_objects[i] = new Particle();
	}
}

ParticleSystem::~ParticleSystem()
{

}

void ParticleSystem::createRadial(float x, float y, uint count)
{
	for (uint i = 0; i < count; i++)
	{
		float angle = 2 * 3.14f * ((float)i / count);
		float vx = glm::cos(angle)*0.5f;
		float vy = glm::sin(angle)*0.5f;

		create(x, y, vx, vy);
	}
}

Particle::Particle() : PoolObject()
{
	
}

Particle::~Particle()
{

}


bool Particle::update()
{
	// Destroy particle if it goes off screen
	if (m_y > ShmupGame::WORLD_UPPER_BOUND_Y ||
		m_y < ShmupGame::WORLD_LOWER_BOUND_Y ||
		m_x > ShmupGame::WORLD_UPPER_BOUND_X ||
		m_x < ShmupGame::WORLD_LOWER_BOUND_X)
	{
		destroy();
		return false;
	}

	// Update with velocity
	m_x += Globals::m_uiManager->getFramerateAdjust(m_vx);
	m_y += Globals::m_uiManager->getFramerateAdjust(m_vy);

	return true;
}

void Particle::create(float x, float y, float vx, float vy)
{
	PoolObject::create(x, y, vx, vy);
	m_x = x;
	m_y = y;
	m_vx = vx;
	m_vy = vy;

}
glm::vec4 Particle::getTransform()
{
	return glm::vec4(m_x, m_y, 0.0f, 0.0f);
}
