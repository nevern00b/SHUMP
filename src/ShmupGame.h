#pragma once

#include "GameManager.h"

class ShmupGame : public GameManager
{

public:

    ShmupGame();
    ~ShmupGame();

    virtual void init();
    virtual void update();

	static const float WORLD_BOUND_X;
	static const float WORLD_BOUND_Y;


private:

    Entity* m_player;

};