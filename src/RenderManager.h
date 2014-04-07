#pragma once

#include <list>
#include <glm/glm.hpp>
#include "Common.h"
#include "Buffer.h"
#include "ShaderCommon.h"

class Entity;

class RenderManager
{
public:
    
    RenderManager();
    ~RenderManager();

    void render();
    void addEntity(Entity* entity);
    void removeEntity(Entity* entity);
    void renderMaterial(const ShaderCommon::MaterialGL& material);
    void renderTransform(const ShaderCommon::TransformGL& transform);

    void setRenderState(uint renderStateBitfield);
    void setViewportSize(uint width, uint height);
    void clearColor(int index, const glm::vec4& color);
    void clearDepth();
    void clearDepthStencil();
    void setTextureParams(GLenum target, GLenum wrapMode, GLenum minFilter, GLenum magFilter, uint numLevels);
    void setSamplerParams(GLuint sampler, GLenum wrapMode, GLenum minFilter, GLenum magFilter);

    GLuint m_skyboxTexture;
    GLuint m_nearestSampler;
    GLuint m_linearSampler;

    // These are set during the render call every frame
    glm::mat4 m_projMatrix;
    glm::mat4 m_viewMatrix;


    bool m_lightBufferDirty; // Update buffer when lighting changes

private:

    GLuint m_basicShader;

    std::list<Entity*> m_entities;
    Buffer<ShaderCommon::MaterialGL>* m_materialBuffer;
    Buffer<ShaderCommon::TransformGL>* m_transformBuffer;
    Buffer<ShaderCommon::PerFrameGL>* m_perFrameBuffer;
    Buffer<ShaderCommon::LightingGL>* m_lightingBuffer;

    
};

namespace RENDER_STATE
{
    const uint CULLING = 1 << 16;
    const uint DEPTH_TEST = 1 << 17;
    const uint DEPTH_WRITE = 1 << 18;
    const uint COLOR = 1 << 19;
    const uint ALPHA_BLEND = 1 << 20;
    const uint STENCIL_TEST = 1 << 21;
    const uint STENCIL_WRITE = 1 << 22;
    const uint FRAMEBUFFER_SRGB = 1 << 23;
    const uint LINEAR_SAMPLING_COLOR = 1 << 24;
}