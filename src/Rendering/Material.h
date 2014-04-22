#pragma once

#include <glm/glm.hpp>
#include "Common.h"

class Material
{
public:

    Material();
    ~Material();
    void render();

    bool m_transparent;
    bool m_cutout;
    GLuint m_diffuseTexture;
    glm::vec4 m_diffuseColor;
    float m_diffuseBlend;
    GLuint m_specularTexture;
    float m_specIntensity;
    float m_specPower;
    float m_specBlend;
    GLuint m_reflectTexture;
    float m_reflectBlend;
    GLuint m_normalTexture;
    float m_normalIntensity;
	bool m_useNoise;
};

