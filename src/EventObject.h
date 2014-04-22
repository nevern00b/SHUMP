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

	virtual void onCollisionEnter(EventObject* collider);
	virtual void onCollisionLeave(EventObject* collider);
};
