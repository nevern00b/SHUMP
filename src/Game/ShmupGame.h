#pragma once

#include "GameManager.h"

class BulletPool;

class ShmupGame : public GameManager
{

public:

	static const int ENEMY_GROUP = -1;
	static const int PLAYER_GROUP = -2;

    ShmupGame();
    ~ShmupGame();

    virtual void init();
    virtual void update();

	BulletPool* getBulletPool(const std::string& color);

	static const float WORLD_BOUND_X;
	static const float WORLD_BOUND_Y;

	BulletPool* m_playerBulletPool;
	BulletPool* m_enemyBulletPool;

private:

    Entity* m_player;

};