#include "Mesh.h"

#include "Buffer.h"
#include "ShaderCommon.h"
#include "Material.h"

Mesh::Mesh(float* vertexData, ushort* elementArrayData, uint numVertices, uint numElements)
{
	init((void*)vertexData, (void*)elementArrayData, numVertices, 32, numElements, 2, { 0 }, false);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vao);
    delete m_vertexBuffer;
    delete m_elementArrayBuffer;
}

void Mesh::init(void* vertexData, void* elementArrayData, uint numVertices, uint vertexSize, uint numElements, uint elementSize, const std::vector<uint>& materialIndices, bool stream)
{
	m_numVertices = numVertices;
	m_numElements = numElements;
	m_materialIndices = materialIndices;
	m_vertexSize = vertexSize;
	m_elementSize = elementSize;

	uint vboSize = vertexSize * numVertices;
	uint iboSize = elementSize * numElements;
	GLenum usage = stream ? GL_STREAM_DRAW : GL_STATIC_DRAW;
	m_vertexBuffer = new Buffer<uchar>(GL_ARRAY_BUFFER, usage, 0, vboSize, (uchar*)vertexData);
	m_elementArrayBuffer = new Buffer<uchar>(GL_ELEMENT_ARRAY_BUFFER, usage, 0, iboSize, (uchar*)elementArrayData);

	// Generate the vertex array object
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// Add the model VBO to the state of the vertex array object
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer->m_bufferObject);

	uint positionOffset = 0;
	uint normalOffset = 12;
	uint uvOffset = 24;

	// Enable vertex attributes
	glEnableVertexAttribArray(ShaderCommon::POSITION_ATTR);
	glEnableVertexAttribArray(ShaderCommon::NORMAL_ATTR);
	if(vertexSize == 32) glEnableVertexAttribArray(ShaderCommon::UV_ATTR);

	// Set the vertex attribute pointers. The vertex attributes are interleaved
	glVertexAttribPointer(ShaderCommon::POSITION_ATTR, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)(positionOffset));
	glVertexAttribPointer(ShaderCommon::NORMAL_ATTR, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)(normalOffset));
	glVertexAttribPointer(ShaderCommon::UV_ATTR, 2, GL_FLOAT, GL_FALSE, vertexSize, (void*)(uvOffset));

	// Add the element array buffer to the state of the vertex array object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementArrayBuffer->m_bufferObject);

	//Unbind everything
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::update(void* vertexData, void* elementArrayData, uint numVertices, uint numElements)
{
	m_numVertices = numVertices;
	m_numElements = numElements;

	m_vertexBuffer->updateAll((uchar*)vertexData);
	m_elementArrayBuffer->updateAll((uchar*)elementArrayData);
}

void Mesh::render(const std::vector<Material*>& materials)
{
    // Set up the vao
    glBindVertexArray(m_vao);
	glDisableVertexAttribArray(ShaderCommon::TRANSFORM_ATTR);

    for (uint i = 0; i < m_materialIndices.size(); i++)
    {
        uint elementIndex = m_materialIndices[i];
        uint elementArrayOffset = elementIndex * 2; // In bytes
        uint numElements = i == m_materialIndices.size() - 1 ? m_numElements - elementIndex : m_materialIndices[i + 1] - elementIndex;
            
        materials[i]->render();

		GLenum type = m_elementSize == 4 ? GL_UNSIGNED_INT : GL_UNSIGNED_SHORT;
        glDrawElements(GL_TRIANGLES, numElements, type, (void*)elementArrayOffset);
    }

    glBindVertexArray(0);    
}

void Mesh::renderInstanced(const std::vector<Material*>& materials, uint count, GLuint transformBuffer)
{
	// Set up the vao for instancing
	glBindVertexArray(m_vao);
	glEnableVertexAttribArray(ShaderCommon::TRANSFORM_ATTR);
	glBindBuffer(GL_ARRAY_BUFFER, transformBuffer);
	glVertexAttribPointer(ShaderCommon::TRANSFORM_ATTR, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribDivisor(ShaderCommon::TRANSFORM_ATTR, 1);

	for (uint i = 0; i < m_materialIndices.size(); i++)
	{
		uint elementIndex = m_materialIndices[i];
		uint elementArrayOffset = elementIndex * 2; // In bytes
		uint numElements = i == m_materialIndices.size() - 1 ? m_numElements - elementIndex : m_materialIndices[i + 1] - elementIndex;

		materials[i]->render();

		GLenum type = m_elementSize == 4 ? GL_UNSIGNED_INT : GL_UNSIGNED_SHORT;
		glDrawElementsInstanced(GL_TRIANGLES, numElements, type, (void*)elementArrayOffset, count);
	}

	glBindVertexArray(0);
}

void Mesh::render()
{
    //glBindVertexArray(m_vao);
    //glDrawElements(GL_TRIANGLES, m_numElements, GL_UNSIGNED_SHORT, 0);
    //glBindVertexArray(0);
}

void Mesh::renderInstanced(uint count, GLuint transformBuffer)
{
	//glBindVertexArray(m_vaoInstanced);
	//glDrawElementsInstanced(GL_TRIANGLES, m_numElements, GL_UNSIGNED_SHORT, 0, count);
	//glBindVertexArray(0);
}