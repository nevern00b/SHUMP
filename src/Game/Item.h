#pragma once

#include "Entity.h"

#include "Game/StateMachine.h"

class Item : public Entity
{
public:
	Item();
	virtual ~Item();

	virtual void update();

protected:
	Entity* m_visual;
};

class ImmunityItem : public Item
{
public:
	ImmunityItem(COLOR color);
	virtual ~ImmunityItem();
};