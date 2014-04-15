#pragma once

#include <glm/glm.hpp>
#include "Common.h"
#include "EventObject.h"
#include "Rendering/Buffer.h"
class Mesh;
class Material;


class ObjectPool
{
public:
	ObjectPool(uint size, Mesh* mesh, Material* material);
	virtual ~ObjectPool();

	virtual void render();

protected:

	uint m_size;
	Mesh* m_mesh;
	Material* m_material;
	Buffer<glm::vec4>* m_transformBuffer;
	std::vector<glm::vec4> m_transformData;
};

