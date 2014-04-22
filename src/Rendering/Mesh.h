#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Common.h"
#include "Buffer.h"

class Material;
struct MeshData;

class Mesh
{

public:

    Mesh(float* vertexData, ushort* elementArrayData, uint numVertices, uint numElements);
    ~Mesh();

	void update(void* vertexData, void* elementArrayData, uint numVertices, uint numElements);

    void render(const std::vector<Material*>& materials);
	void renderInstanced(const std::vector<Material*>& materials, uint count, GLuint transformBuffer);

	void render();
	void renderInstanced(uint count, GLuint transformBuffer);


private:

	void init(void* vertexData, void* elementArrayData, uint numVertices, uint vertexSize, uint numElements, uint elementSize, const std::vector<uint>& materialIndices, bool stream);

    Buffer<uchar>* m_vertexBuffer;
    Buffer<uchar>* m_elementArrayBuffer;
    GLuint m_vao;
    uint m_numVertices;
    uint m_numElements;
	uint m_vertexSize;
	uint m_elementSize;
    std::vector<uint> m_materialIndices;
};
