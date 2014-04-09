#include "PhysicsManager.h"


#include <Box2D/Box2D.h>
#include <glm/gtc/type_ptr.hpp>
#include "Globals.h"
#include "UIManager.h"
#include "Common.h"
#include "Entity.h"
#include "PhysicsComponent.h"
#include "GameManager.h"

const float PhysicsManager::PHYSICS_SCALE = 1.0f / 100.0f;
const float PhysicsManager::PHYSICS_TIMESTEP = 1.0f / 60.0f;
const int PhysicsManager::POSITION_ITERATIONS = 3;
const int PhysicsManager::VELOCITY_ITERATIONS = 8;
const uint PhysicsManager::MASK_DEFAULT = 0xFFFF;
const uint PhysicsManager::COLLISION_NONE = 0x00;
const uint PhysicsManager::COLLISION_DEFAULT = 0x01;

PhysicsManager::PhysicsManager()
{
   // Create world
    m_world = new b2World(b2Vec2(0.0f, 0.0f));
    m_world->SetAllowSleeping(false);
    b2ContactListener* contactListener = new ContactListener();
    m_world->SetContactListener(contactListener);
}

PhysicsManager::~PhysicsManager()
{
    delete m_world;
}

void PhysicsManager::update()
{
    m_world->Step(PHYSICS_TIMESTEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
    m_world->ClearForces();

    // Destroy the bodies that were marked for destruction during the timestep
    destroyMarkedBodies();
}

void PhysicsManager::destroyPhysicsComponent(PhysicsComponent* physicsComponent)
{
    b2Body* body = physicsComponent->m_body;
    body->SetUserData(0);
    m_bodiesToDestroy.push_back(body);
    // Body is fully destroyed after the time step
}


void PhysicsManager::destroyMarkedBodies()
{
    for (auto& body : m_bodiesToDestroy)
    {
        m_world->DestroyBody(body);
    }

    m_bodiesToDestroy.clear();
}

ContactListener::ContactListener() : b2ContactListener()
{

}

void ContactListener::BeginContact(b2Contact* contact)
{
    Entity* obj1 = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
    Entity* obj2 = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();
    
    if (obj1 != 0 && obj2 != 0)
    {
        obj1->onCollisionEnter(obj2);
        obj2->onCollisionEnter(obj1);
    }
}

void ContactListener::EndContact(b2Contact* contact)
{
    Entity* obj1 = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
    Entity* obj2 = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();

    if (obj1 != 0 && obj2 != 0)
    {
        obj1->onCollisionLeave(obj2);
        obj2->onCollisionEnter(obj1);
    }
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}

namespace Utils
{
    b2PolygonShape* createBoxShape(float width, float height)
    {
        b2PolygonShape* shape = new b2PolygonShape();
        shape->SetAsBox(width / 2, height / 2);
        return shape;
    }

    b2CircleShape* createCircleShape(float radius)
    {
        b2CircleShape* shape = new b2CircleShape();
        shape->m_radius = radius;
        return shape;
    }

    b2PolygonShape* createPolyShape(const std::vector<b2Vec2>& points)
    {
        // Only creates convex hull shapes for now. Concave shapes require triangulation.
        b2PolygonShape* shape = new b2PolygonShape();
        shape->Set(&points[0], points.size());
        return shape;
    }



}
