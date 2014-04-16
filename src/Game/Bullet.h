#pragma once

#include <vector>
#include <Box2D/Box2D.h>
#include "Common.h"
#include "Rendering/ObjectPool.h"
#include "EventObject.h"
#include "StateMachine.h"

class Mesh;
class Material;
struct PhysicsData;
class Bullet;

class Bullet : public EventObject
{

public:
	Bullet(const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef, COLOR color);
	~Bullet();
	
	bool update();
	void create(float x, float y, float vx, float vy);
	void destroy();

	bool m_disabled;
	b2Body* m_body;
	float m_damage;
	COLOR m_color;

private:
	

};