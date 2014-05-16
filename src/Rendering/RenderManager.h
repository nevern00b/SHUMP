#pragma once

#include <list>
#include <glm/glm.hpp>
#include "Common.h"
#include "Buffer.h"
#include "ShaderCommon.h"
#include "Game/StateMachine.h"

class Entity;
class Shader;
class ObjectPool;
class FullScreenQuad;
class Background;
class Timer;
class Floor;
class Mesh;

class RenderManager
{
public:
    
    RenderManager();
    ~RenderManager();

	void resizeWindow(int width, int height);
    void render();
	glm::mat4 getShadowMatrix();
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

	float m_floorDepth = -2.0f;

private:

	

    Shader* m_basicShader;
	Shader* m_noiseShader;
	Shader* m_floorShader;
	Shader* m_backgroundShader;
	Shader* m_bulletShader;
	Shader* m_finalOutputShader;
	Shader* m_bloomShader;
	Shader* m_blurShaders[2];

	Shader* m_basicShadowShader;
	Shader* m_bulletShadowShader;
	Shader* m_noiseShadowShader;

	// Group things by rendering type
	std::list<Entity*> m_noiseEntities;
    std::list<Entity*> m_entities;
	std::list<ObjectPool*> m_objectPools;

	Mesh* m_floor;

	FullScreenQuad* m_fullScreenQuad;

	// FBO stuff
    GLuint m_defaultFBO;
	GLenum m_fboAttachments[ShaderCommon::NUM_FBO_BINDINGS];
	GLuint m_fbo;
	GLuint m_colorTexture; // Screen sized
	GLuint m_depthTexture; // Screen sized

	GLuint m_bloomFBOs[2];
	GLuint m_bloomTextures[2];
	uint m_bloomSizeX;
	uint m_bloomSizeY;

	GLuint m_backgroundFBO;
	GLuint m_backgroundTexture;
	uint m_backgroundSizeX;
	uint m_backgroundSizeY;
};

namespace RENDER_STATE
{
    const uint CULLING = 1 << 16;
    const uint DEPTH_TEST = 1 << 17;
    const uint DEPTH_WRITE = 1 << 18;
    const uint COLOR = 1 << 19;
    const uint ALPHA_BLEND = 1 << 20;
    const uint STENCIL_TEST_EQUAL = 1 << 21;
	const uint STENCIL_TEST_NEQUAL = 1 << 22;
    const uint STENCIL_WRITE = 1 << 23;
    const uint FRAMEBUFFER_SRGB = 1 << 24;
    const uint LINEAR_SAMPLING_COLOR = 1 << 25;
}

namespace STENCIL_VALUE
{
	const uint SHADOW = 1 << 0;
	const uint SOLID = 1 << 1;
	//const uint REFLECTION = 1 << 2;
}