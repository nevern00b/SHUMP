#include "ObjectPool.h"

#include "Globals.h"
#include "Mesh.h"
#include "RenderManager.h"

ObjectPool::ObjectPool(uint size, Mesh* mesh, Material* material) :
	m_mesh(mesh),
	m_material(material),
	m_size(size),
	m_transformData(size)
{
	m_transformBuffer = new Buffer<glm::vec4>(GL_ARRAY_BUFFER, GL_STREAM_DRAW, 0, m_size, 0);
	mesh->initInstanced(m_transformBuffer->m_bufferObject);
	Globals::m_renderManager->addObjectPool(this);
}

ObjectPool::~ObjectPool()
{
	Globals::m_renderManager->removeObjectPool(this);
	delete m_transformBuffer;
}

void ObjectPool::render()
{

}
