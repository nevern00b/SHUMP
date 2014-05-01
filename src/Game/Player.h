#pragma once

#include "Common.h"
#include "Entity.h"
#include <Box2D/Box2D.h>

class BulletPool;
class ShootComponent;
class Timer;
class Minion;
class b2Vec2;

class Player : public Entity
{
public:
    Player();
    virtual ~Player();

    virtual bool update();
	virtual void onCollide(EventObject* collider);

	void changeColor();
	void gainLives(uint lives);
	b2Vec2 GetPosition();

private:

	void shoot();

	Timer* m_shootTimer;
	uint m_lives;
	ShootComponent* m_shootComponent;

};
