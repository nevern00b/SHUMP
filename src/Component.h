#pragma once

#include <vector>

class Entity;

class Component
{
public:
    Component();
    Component(Entity* entity);
    virtual ~Component();
        
    Entity* m_entity;
};