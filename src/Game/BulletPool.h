#pragma once

#include <vector>
#include <Box2D/Box2D.h>
#include "Common.h"
#include "Rendering/ObjectPool.h"
#include "EventObject.h"
#include "StateMachine.h"
#include "Globals.h"

class Mesh;
class Material;
struct PhysicsData;
class Bullet;

class BulletPool : public ObjectPool
{
public:
	BulletPool(uint size, Mesh* mesh, Material* material, const PhysicsData& physicsData, COLOR color);
	virtual ~BulletPool();
};