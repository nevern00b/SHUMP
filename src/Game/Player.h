#pragma once

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

	uint m_lives;

private:

	void shoot();

	Timer* m_shootTimer;
	ShootComponent* m_shootComponent;

};