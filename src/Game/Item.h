#pragma once

#include "Entity.h"

#include "Game/StateMachine.h"

class Item : public Entity
{
public:
	Item(float vx, float vy);
	virtual ~Item();

	virtual bool update();

protected:
	Entity* m_visual;
};

class ImmunityItem : public Item
{
public:
	ImmunityItem(COLOR color, float vx, float vy);
	virtual ~ImmunityItem();

	COLOR m_color;
};

class LifeItem : public Item
{
public:
	LifeItem(float vx, float vy);
	virtual ~LifeItem();
};