#pragma once

class EventObject
{
public:
	EventObject();
	virtual ~EventObject();

	virtual void onCollisionEnter(EventObject* collider);
	virtual void onCollisionLeave(EventObject* collider);

};