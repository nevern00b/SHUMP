#pragma once
#include <Box2D/Box2D.h>
#include "Common.h"
#include "Entity.h"

#define Max_Minion_Count 10

class BulletPool;
class ShootComponent;
class Timer;
class Minion;
struct b2Vec2;

class Player : public Entity
{
public:
    Player();
    virtual ~Player();

    virtual bool update();
	virtual void onCollide(EventObject* collider);

	void changeColor();
	void gainLives(uint lives);
	void gainMinions(uint newMinions);
	b2Vec2 getPosition();

	uint m_lives;
	uint m_minionCount;

private:

	void shoot();

	Timer* m_shootTimer;
	ShootComponent* m_shootComponent;

};
