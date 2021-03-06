#pragma once

#include <Box2D/Box2D.h>
#include <vector>
#include <glm/glm.hpp>
#include "Utils.h"

class b2World;
class PhysicsComponent;
class ContactListener;

class PhysicsManager
{
public:
    PhysicsManager();
    ~PhysicsManager();
    void update();

    static const uint MASK_DEFAULT;
    static const uint COLLISION_NONE;
    static const uint COLLISION_DEFAULT;
	static const uint COLLISION_RED;
	static const uint COLLISION_GREEN;
	static const uint COLLISION_BLUE;
	static const uint COLLISION_YELLOW;


    b2World* m_world;

private:    

	ContactListener* m_contactListener;
	float m_accumulator; // For timestep

};

class ContactListener : public b2ContactListener
{
public:
    ContactListener();

private:
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);

    // Useful for getting the impulse of a collision
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};