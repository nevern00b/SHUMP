#include "FullScreenQuad.h"

#include <glm/glm.hpp>
#include "ShaderCommon.h"

FullScreenQuad::FullScreenQuad()
{
    // Create buffer objects and vao for a full screen quad
    const uint numVertices = 4;
    glm::vec2 vertices[numVertices];
    vertices[0] = glm::vec2(-1.0, -1.0);
    vertices[1] = glm::vec2(1.0, -1.0);
    vertices[2] = glm::vec2(1.0, 1.0);
    vertices[3] = glm::vec2(-1.0, 1.0);

    const uint numElements = 6;
    unsigned short elements[numElements] = {0, 1, 2, 2, 3, 0};

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*numVertices, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short)*numElements, elements, GL_STATIC_DRAW);

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glEnableVertexAttribArray(ShaderCommon::POSITION_ATTR);
    glVertexAttribPointer(ShaderCommon::POSITION_ATTR, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

    //Unbind everything
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

FullScreenQuad::~FullScreenQuad()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ibo);
}

void FullScreenQuad::render()
{
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    glBindVertexArray(0);
}