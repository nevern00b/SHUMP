#pragma once

#include "Common.h"
#include "Entity.h"
class BulletPool;

class Player : public Entity
{
public:
    Player();
    virtual ~Player();

    virtual void update();

private:

	void shoot();

	uint m_shootFrames;
};