#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
    Player();
    virtual ~Player();

    virtual void update();

private:
    void shoot();
};