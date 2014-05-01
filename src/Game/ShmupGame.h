#pragma once

#include "GameManager.h"

class BulletPool;
class ParticleSystem;
class Player;
class EnemyManager;
class Timer;

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
	Player* getPlayer(); 

	static const float ShmupGame::WORLD_UPPER_BOUND_X;
	static const float ShmupGame::WORLD_LOWER_BOUND_X;
	static const float ShmupGame::WORLD_UPPER_BOUND_Y;
	static const float ShmupGame::WORLD_LOWER_BOUND_Y;

	BulletPool* m_yellowBulletPool;
	BulletPool* m_greenBulletPool;
	BulletPool* m_blueBulletPool;
	BulletPool* m_redBulletPool;
	BulletPool* m_enemyRBulletPool;
	BulletPool* m_enemyBBulletPool;
	BulletPool* m_enemyGBulletPool;
	BulletPool* m_enemyYBulletPool;
	ParticleSystem* m_particleSystem;
	Player* m_player;

private:

	Timer* m_scoreTimer;
	EnemyManager* m_enemyManager;

};