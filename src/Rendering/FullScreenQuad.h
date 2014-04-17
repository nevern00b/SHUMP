#pragma once

#include "Common.h"

class FullScreenQuad
{

public:

    FullScreenQuad();
    ~FullScreenQuad();

    void render();

private:

    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ibo;

};