#include "EventObject.h"

EventObject::EventObject()
{

}

EventObject::~EventObject()
{

}

void EventObject::onCollisionEnter(EventObject* collider)
{
	// Overriden in Entity
}

bool EventObject::update()
{
	return true;
	// Overriden
}