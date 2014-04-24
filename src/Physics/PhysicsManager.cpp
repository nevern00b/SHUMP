#include "PhysicsManager.h"

#include <Box2D/Box2D.h>
#include <glm/gtc/type_ptr.hpp>
#include "Globals.h"
#include "UIManager.h"
#include "Common.h"
#include "Entity.h"
#include "GameManager.h"
#include "EventObject.h"
#include "PhysicsComponent.h"

const uint PhysicsManager::MASK_DEFAULT = 0xFFFF;
const uint PhysicsManager::COLLISION_NONE = 0x00;
const uint PhysicsManager::COLLISION_DEFAULT = 0x01;
const uint PhysicsManager::COLLISION_RED = 0x02;
const uint PhysicsManager::COLLISION_GREEN = 0x04;
const uint PhysicsManager::COLLISION_BLUE = 0x08;
const uint PhysicsManager::COLLISION_YELLOW = 0x10;

PhysicsManager::PhysicsManager() :
	m_accumulator(0.0f)
{
   // Create world
    m_world = new b2World(b2Vec2(0.0f, 0.0f));
    m_world->SetAllowSleeping(false);
	m_world->SetAutoClearForces(false);
    m_contactListener = new ContactListener();
	m_world->SetContactListener(m_contactListener);
}

PhysicsManager::~PhysicsManager()
{
    delete m_world;
	delete m_contactListener;
}

void PhysicsManager::update()
{
	float timeStep = 1.0f / 100.0f;
	float frameTime = Globals::m_uiManager->m_frameTime;

	bool clearForces = false;

	m_accumulator += frameTime;

	while (m_accumulator >= timeStep)
	{
		m_accumulator -= timeStep;

		// Use a non-fixed time step for the last step, should not exceed timestep * 2
		if (m_accumulator < timeStep)
		{
			timeStep += m_accumulator;
			m_accumulator = 0.0f;
		}

		m_world->Step(timeStep, 8, 3);
		clearForces = true;
	}
	
	if (clearForces)
	{
		m_world->ClearForces();
	}
}

ContactListener::ContactListener() : b2ContactListener()
{

}

void ContactListener::BeginContact(b2Contact* contact)
{
	EventObject* obj1 = (EventObject*)contact->GetFixtureA()->GetBody()->GetUserData();
	EventObject* obj2 = (EventObject*)contact->GetFixtureB()->GetBody()->GetUserData();
    
    if (obj1 != 0 && obj2 != 0)
    {
        obj1->onCollisionEnter(obj2);
        obj2->onCollisionEnter(obj1);
    }
}

void ContactListener::EndContact(b2Contact* contact)
{
	//EventObject* obj1 = (EventObject*)contact->GetFixtureA()->GetBody()->GetUserData();
	//EventObject* obj2 = (EventObject*)contact->GetFixtureB()->GetBody()->GetUserData();
	//
    //if (obj1 != 0 && obj2 != 0)
    //{
    //    obj1->onCollisionLeave(obj2);
    //    obj2->onCollisionEnter(obj1);
    //}
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}
