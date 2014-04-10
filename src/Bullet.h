#pragma once

#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet(Entity* ship);
	virtual ~Bullet();
	virtual void update();
};