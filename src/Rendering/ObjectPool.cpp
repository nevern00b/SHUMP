#include "ObjectPool.h"

#include "Globals.h"
#include "Mesh.h"
#include "RenderManager.h"

ObjectPool::ObjectPool(uint size, Mesh* mesh, Material* material) :
	m_mesh(mesh),
	m_material(material),
	m_size(size),
	m_transformData(size),
	m_objects(size)
{
	m_transformBuffer = new Buffer<glm::vec4>(GL_ARRAY_BUFFER, GL_STREAM_DRAW, 0, m_size, 0);
	Globals::m_renderManager->addObjectPool(this);
}

ObjectPool::~ObjectPool()
{
	Globals::m_renderManager->removeObjectPool(this);
	delete m_transformBuffer;
}

void ObjectPool::create(float x, float y, float vx, float vy)
{
	// Find the first available object and create it
	for (uint i = 0; i < m_size; i++)
	{
		PoolObject* object = m_objects[i];
		if (object->m_disabled)
		{
			object->create(x, y, vx, vy);
			break;
		}
	}
}


void ObjectPool::render()
{
	uint count = 0;
	for (uint i = 0; i < m_size; i++)
	{
		PoolObject* object = m_objects[i];
		if (!object->m_disabled)
		{
			if (object->update())
			{
				m_transformData[count] = object->getTransform();
				count++;
			}
		}
	}

	if (count == 0) return;
	m_transformBuffer->updateRange(0, count, &m_transformData[0], true);
	m_mesh->renderInstanced({ m_material }, count, m_transformBuffer->m_bufferObject);
}

PoolObject::PoolObject() : EventObject(),
	m_disabled(true)
{

}

PoolObject::~PoolObject()
{

}

bool PoolObject::update()
{
	return true;
}

void PoolObject::create(float x, float y, float vx, float vy)
{
	m_disabled = false;
}

void PoolObject::destroy()
{
	m_disabled = true;
}

glm::vec4 PoolObject::getTransform()
{
	return glm::vec4();
}
