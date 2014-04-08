#pragma once

#include "GameManager.h"

class ShmupGame : public GameManager
{

public:

    ShmupGame();
    ~ShmupGame();

    virtual void init();
    virtual void update();

private:

    Entity* m_player;

};