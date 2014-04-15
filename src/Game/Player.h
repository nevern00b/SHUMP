#pragma once

#include "Common.h"
#include "Entity.h"
class BulletPool;
class ShootComponent;

class Player : public Entity
{
public:
    Player();
    virtual ~Player();

    virtual void update();
	virtual void onCollisionEnter(EventObject* collider);

	void changeColor();

private:

	void shoot();

	ShootComponent* m_shootComponent;
	uint m_shootFrames;
};