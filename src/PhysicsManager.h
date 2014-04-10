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
    void destroyPhysicsComponent(PhysicsComponent* physicsComponent);

    static const uint MASK_DEFAULT;
    static const uint COLLISION_NONE;
    static const uint COLLISION_DEFAULT;

    b2World* m_world;

	// Share these defs when creating objects
	b2BodyDef m_sharedBodyDef;
	b2FixtureDef m_sharedFixtureDef;
	b2Shape* m_squareBig;
	b2Shape* m_squareSmall;

private:    

    void destroyMarkedBodies();

    std::vector<b2Body*> m_bodiesToDestroy;
	ContactListener* m_contactListener;


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

namespace Utils
{
    b2PolygonShape* createBoxShape(float width, float height);
    b2CircleShape* createCircleShape(float radius);
    b2PolygonShape* createPolyShape(const std::vector<b2Vec2>& points); // TO-DO: or except glm::vec2?
}