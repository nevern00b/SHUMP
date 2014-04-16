#pragma once

#include <glm/glm.hpp>
#include "Common.h"
#include "EventObject.h"
#include "Rendering/Buffer.h"
class Mesh;
class Material;
class PoolObject;


class ObjectPool
{
public:
	ObjectPool(uint size, Mesh* mesh, Material* material);
	virtual ~ObjectPool();
	

	void create(float x, float y, float vx, float vy);
	void render();

protected:

	uint m_size;
	Mesh* m_mesh;
	Material* m_material;
	Buffer<glm::vec4>* m_transformBuffer;
	std::vector<glm::vec4> m_transformData;
	std::vector<PoolObject*> m_objects;
};

class PoolObject : public EventObject
{
public:
	PoolObject();
	virtual ~PoolObject();

	virtual bool update();
	virtual void create(float x, float y, float vx, float vy);
	virtual void destroy();
	virtual glm::vec4 getTransform();

	bool m_disabled;

};