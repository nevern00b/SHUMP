#pragma once

#include "GameManager.h"

class BulletPool;
class ParticleSystem;
class Player;
class EnemyManager;

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

	BulletPool* m_yellowBulletPool;
	BulletPool* m_greenBulletPool;
	BulletPool* m_blueBulletPool;
	BulletPool* m_redBulletPool;
	BulletPool* m_enemyBulletPool;
	ParticleSystem* m_particleSystem;

private:

    Player* m_player;
	EnemyManager* m_enemyManager;

};