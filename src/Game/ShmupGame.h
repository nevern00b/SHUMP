#pragma once

#include "GameManager.h"

class BulletPool;

class ShmupGame : public GameManager
{

public:

    ShmupGame();
    ~ShmupGame();

    virtual void init();
    virtual void update();

	static const float WORLD_BOUND_X;
	static const float WORLD_BOUND_Y;

	BulletPool* m_playerBulletPool;

private:

    Entity* m_player;

};