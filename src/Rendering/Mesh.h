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

    Mesh(float* vertexData, ushort* elementArrayData, uint numVertices, uint numElements, const std::vector<uint>& materialIndices);
    ~Mesh();

	void initInstanced(GLuint transformBuffer);

    void render(const std::vector<Material*>& materials);
	void renderInstanced(const std::vector<Material*>& materials, uint count);

	void render();
	void renderInstanced(uint count);

private:

	GLuint initVao();

    Buffer<float>* m_vertexBuffer;
    Buffer<ushort>* m_elementArrayBuffer;
    GLuint m_vao;
	GLuint m_vaoInstanced;
    uint m_numVertices;
    uint m_numElements;
    std::vector<uint> m_materialIndices;
};
