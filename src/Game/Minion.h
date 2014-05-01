#pragma once

#include "Entity.h"
#include "Common.h"
#include <Box2D/Box2D.h>

class ShootComponent;
class Timer;
class Player;

class Minion : public Entity
{
public:
	Minion(b2Vec2 relativePos);
	virtual ~Minion();

	virtual bool update();
	virtual void onCollide(EventObject* collider);

private:
	void shoot();

	Player* m_player;
	Timer *m_shootTimer;
	ShootComponent* m_shootComponent;
	b2Vec2 m_relativePos;

	uint m_lives;

};