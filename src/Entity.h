#pragma once

#include <vector>
#include <list>
#include <glm/glm.hpp>
#include "Transform.h"

class PhysicsComponent;
struct EntityData;
class Mesh;
class Material;

class Entity
{
public:

    Entity(Entity* parent, EntityData* data, const Transform& transform);
    virtual ~Entity();

    virtual void update();
    void render();
    glm::vec3 getPosition();

    Entity* m_parent;
    std::list<Entity*> m_children;
    std::string m_name;
    
    glm::mat4 m_renderMatrix;

    Mesh* m_mesh;
    std::vector<Material*> m_materials;
    Transform* m_transform; // Equals m_physics if entity has physics
    PhysicsComponent* m_physics;

private:
    
};

struct EntityData
{
    EntityData();
    Mesh* m_mesh;
    std::vector<Material*> m_materials;
};