#pragma once

#include <vector>
#include <list>
#include <glm/glm.hpp>
#include "Transform.h"
#include "EventObject.h"

class PhysicsComponent;
class Mesh;
class Material;
struct PhysicsData;
class Component;
class RenderComponent;

class Entity : public EventObject
{
public:

    Entity(Entity* parent);
    virtual ~Entity();
	void destroy();

	void setParent(Entity* parent);

    virtual bool update();
	virtual void onCollisionEnter(EventObject* collider);
	virtual void onCollide(EventObject* collider);
	
	//should make this virtual(?) because Enemy has to have its own render class
	void render();
    
	glm::vec3 getPosition();

    Entity* m_parent;
    std::list<Entity*> m_children;
    std::string m_name;
    glm::mat4 m_renderMatrix;
	bool m_dead;

	// Components
    RenderComponent* m_render;
    Transform* m_transform; // Equals m_physics if entity has physics
    PhysicsComponent* m_physics;
    std::list<Component*> m_components;

	// Object that collided with it this frame
	EventObject* m_collider;
};