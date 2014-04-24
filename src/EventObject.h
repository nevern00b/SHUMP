#pragma once

#include <string>

enum ObjectType
{
	DEFAULT,
	BULLET,
	ENEMY,
	PLAYER
};

class EventObject
{
public:
	EventObject();
	virtual ~EventObject();

	virtual bool update();
	virtual void onCollisionEnter(EventObject* collider);
};

