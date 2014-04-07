#include "Mesh.h"

#include "Buffer.h"
#include "ShaderCommon.h"
#include "Material.h"

Mesh::Mesh(float* vertexData, ushort* elementArrayData, uint numVertices, uint numElements, const std::vector<uint>& materialIndices) :
    m_numVertices(numVertices),
    m_numElements(numElements),
    m_materialIndices(materialIndices)
{
    uint numFloats = m_numVertices * 8;
    m_vertexBuffer = new Buffer<float>(GL_ARRAY_BUFFER, GL_STATIC_DRAW, 0, numFloats, vertexData);
    m_elementArrayBuffer = new Buffer<ushort>(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, 0, m_numElements, elementArrayData);

    // Generate the vertex array object
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Add the model VBO to the state of the vertex array object
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer->m_bufferObject);

    uint vertexSize = 32; // In bytes
    uint positionOffset = 0;
    uint normalOffset = 12;
    uint uvOffset = 24;

    // Enable vertex attributes
    glEnableVertexAttribArray(ShaderCommon::POSITION_ATTR);
    glEnableVertexAttribArray(ShaderCommon::NORMAL_ATTR);
    glEnableVertexAttribArray(ShaderCommon::UV_ATTR);

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

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vao);
    delete m_vertexBuffer;
    delete m_elementArrayBuffer;
}

void Mesh::render(const std::vector<Material*>& materials)
{
    // Bind vertex array
    glBindVertexArray(m_vao);

    for (uint i = 0; i < m_materialIndices.size(); i++)
    {
        uint elementIndex = m_materialIndices[i];
        uint elementArrayOffset = elementIndex * 2; // In bytes
        uint numElements = i == m_materialIndices.size() - 1 ? m_numElements - elementIndex : m_materialIndices[i + 1] - elementIndex;
            
        materials[i]->render();

        glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_SHORT, (void*)elementArrayOffset);
    }

    glBindVertexArray(0);    
}

void Mesh::render()
{
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_numElements, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);
}