#include "Material.h"

#include "ShaderCommon.h"
#include "Globals.h"
#include "RenderManager.h"

Material::Material() :
    m_transparent(false),
    m_cutout(false),
    m_diffuseTexture(0),
    m_diffuseColor(1, 1, 1, 1),
    m_diffuseBlend(0.0),
    m_specularTexture(0),
    m_specIntensity(1.0),
    m_specPower(50.0),
    m_specBlend(0.0),
    m_reflectTexture(0),
    m_reflectBlend(0.0),
    m_normalTexture(0),
    m_normalIntensity(0.0)
{

}

Material::~Material()
{

}

void Material::render()
{
    ShaderCommon::MaterialGL materialGL;
    materialGL.diffuseColor = m_diffuseColor;
    materialGL.diffuseBlend = m_diffuseBlend;
    materialGL.reflectBlend = m_reflectBlend;
    materialGL.specIntensity = m_specIntensity;
    materialGL.specPower = m_specPower;
    materialGL.specBlend = m_specBlend;
    materialGL.normalIntensity = m_normalIntensity;

    Globals::m_renderManager->renderMaterial(materialGL);

    // Bind textures
    if (m_diffuseTexture != 0)
    {
        glActiveTexture(GL_TEXTURE0 + ShaderCommon::DIFFUSE_TEXTURE);
        glBindTexture(GL_TEXTURE_2D, m_diffuseTexture);
    }

    if (m_specularTexture != 0)
    {
        glActiveTexture(GL_TEXTURE0 + ShaderCommon::SPECULAR_TEXTURE);
        glBindTexture(GL_TEXTURE_2D, m_specularTexture);
    }

    if (m_normalTexture != 0)
    {
        glActiveTexture(GL_TEXTURE0 + ShaderCommon::NORMAL_TEXTURE);
        glBindTexture(GL_TEXTURE_2D, m_normalTexture);
    }

    if (m_reflectTexture != 0)
    {
        glActiveTexture(GL_TEXTURE0 + ShaderCommon::REFLECT_TEXTURE);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_reflectTexture);
    }
}
