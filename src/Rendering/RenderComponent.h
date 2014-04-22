#pragma once

#include "Component.h"

class Mesh;
class Material;

class RenderComponent : public Component
{

public:

    RenderComponent(Entity* entity, Mesh* mesh, Material* material);
    virtual ~RenderComponent();
    void render();

	void setMaterial(Material* material);

	std::vector<Material*> m_materials;

private:

    Mesh* m_mesh;
    

};