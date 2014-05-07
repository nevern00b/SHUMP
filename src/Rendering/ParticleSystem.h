#pragma once

#include "ObjectPool.h"

class Mesh;
class Material;

class ParticleSystem : public ObjectPool
{
public:

	ParticleSystem(uint size, Mesh* mesh, Material* material);
	virtual ~ParticleSystem();
	void createRadial(float x, float y, uint count);
};

class Particle : public PoolObject
{
public:
	Particle();
	virtual ~Particle();

	virtual bool update();
	virtual void create(float x, float y, float vx, float vy);
	virtual glm::vec4 getTransform();

	float m_x;
	float m_y;
	float m_z;
	float m_vx;
	float m_vy;
	float m_vz;
};