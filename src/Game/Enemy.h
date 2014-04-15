#pragma once

#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy();
	virtual ~Enemy();
	virtual void update();

	virtual void onCollisionEnter(EventObject* collider);
	virtual void onCollisionLeave(EventObject* collider);

private:
	float m_health;
};