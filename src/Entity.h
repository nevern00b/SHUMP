#pragma once

#include <vector>
#include <list>
#include <glm/glm.hpp>
#include "Transform.h"

class PhysicsComponent;
class Mesh;
class Material;
struct PhysicsData;
class Component;
class RenderComponent;

class Entity
{
public:

    Entity(Entity* parent);
    virtual ~Entity();
	void destroy();

    virtual void update();
    void render();
    glm::vec3 getPosition();

    void onCollisionEnter(Entity* collider);
    void onCollisionLeave(Entity* collider);

    Entity* m_parent;
    std::list<Entity*> m_children;
    std::string m_name;
    
    glm::mat4 m_renderMatrix;

    RenderComponent* m_render;
    Transform* m_transform; // Equals m_physics if entity has physics
    PhysicsComponent* m_physics;

    std::list<Component*> m_components;

	bool m_dead;
    
};