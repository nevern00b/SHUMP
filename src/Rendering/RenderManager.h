#pragma once

#include <list>
#include <glm/glm.hpp>
#include "Common.h"
#include "Buffer.h"
#include "ShaderCommon.h"

class Entity;
class Shader;
class ObjectPool;
class FullScreenQuad;

class RenderManager
{
public:
    
    RenderManager();
    ~RenderManager();

	void resizeWindow(int width, int height);
    void render();
	void addObjectPool(ObjectPool* objectPool);
	void removeObjectPool(ObjectPool* objectPool);
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

    GLuint m_nearestSampler;
    GLuint m_linearSampler;

    // These are set during the render call every frame
    glm::mat4 m_projMatrix;
    glm::mat4 m_viewMatrix;

    bool m_lightBufferDirty; // Update buffer when lighting changes
	Shader* m_activeShader;

	Buffer<ShaderCommon::MaterialGL>* m_materialBuffer;
	Buffer<ShaderCommon::TransformGL>* m_transformBuffer;
	Buffer<ShaderCommon::PerFrameGL>* m_perFrameBuffer;
	Buffer<ShaderCommon::LightingGL>* m_lightingBuffer;

	



private:

    GLuint m_basicShader;
	GLuint m_instancedShader;
	GLuint m_finalOutputShader;
	GLuint m_bloomShader;
	GLuint m_blurShaders[2];

    std::list<Entity*> m_entities;
	std::list<ObjectPool*> m_objectPools;

	FullScreenQuad* m_fullScreenQuad;

	// FBO stuff
	GLenum m_fboAttachments[ShaderCommon::NUM_FBO_BINDINGS];
	GLuint m_fbo;
	GLuint m_colorTexture; // Screen sized
	GLuint m_depthTexture; // Screen sized

	GLuint m_bloomFBOs[2];
	GLuint m_bloomTextures[2]; // 1024x1024 with mipmapping
	uint m_bloomSize;
	uint m_bloomLevels;

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