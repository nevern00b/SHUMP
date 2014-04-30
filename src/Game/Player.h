#pragma once
#include <Box2D/Box2D.h>
#include "Common.h"
#include "Entity.h"
class BulletPool;
class ShootComponent;
class Timer;

class Player : public Entity
{
public:
    Player();
    virtual ~Player();

    virtual bool update();
	virtual void onCollide(EventObject* collider);

	void changeColor();

	void gainLives(uint lives);

	b2Vec2 getPosition2d();

	uint m_lives;

private:

	void shoot();

	Timer* m_shootTimer;
	ShootComponent* m_shootComponent;

};