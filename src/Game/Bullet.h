#pragma once

#include <vector>
#include <Box2D/Box2D.h>
#include "Common.h"
#include "Rendering/ObjectPool.h"
#include "EventObject.h"
class Mesh;
class Material;
struct PhysicsData;
class Bullet;

class BulletPool : public ObjectPool
{
public:
	BulletPool(uint size, Mesh* mesh, Material* material, const PhysicsData& physicsData);
	virtual ~BulletPool();
	virtual void render();
	void shoot(float x, float y, float vx, float vy);

private:

	std::vector<Bullet*> m_bullets;

};

class Bullet : public EventObject
{

public:
	Bullet(const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef);
	~Bullet();
	
	bool update();
	void enable(float x, float y, float vx, float vy);
	void disable();

	bool m_disabled;
	b2Body* m_body;

private:
	

};