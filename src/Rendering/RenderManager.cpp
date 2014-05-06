#include "RenderManager.h"

#include <functional>
#include <glm/gtc/matrix_transform.hpp>
#include "Utils.h"
#include "ShaderCommon.h"
#include "Globals.h"
#include "UIManager.h"
#include "GameManager.h"
#include "Camera.h"
#include "DataManager.h"
#include "Mesh.h"
#include "Light.h"
#include "Game/ShmupGame.h"
#include "ObjectPool.h"
#include "FullScreenQuad.h"
#include "RenderComponent.h"
#include "Material.h"
#include "Shader.h"

RenderManager::RenderManager() :
    m_lightBufferDirty(false),
	m_floor(0),
	m_background(0)
{

    int defaultFBO;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &defaultFBO);
    m_defaultFBO = (GLuint)defaultFBO;

    // Init GL state
    glClearColor(1, 1, 1, 1);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRangef(0.0f, 1.0f);

    // Init buffers
    m_materialBuffer = new Buffer<ShaderCommon::MaterialGL>(GL_UNIFORM_BUFFER, GL_STREAM_DRAW, ShaderCommon::MATERIAL_UBO, 1, 0);
    m_transformBuffer = new Buffer<ShaderCommon::TransformGL>(GL_UNIFORM_BUFFER, GL_STREAM_DRAW, ShaderCommon::TRANSFORM_UBO, 1, 0);
    m_perFrameBuffer = new Buffer<ShaderCommon::PerFrameGL>(GL_UNIFORM_BUFFER, GL_STREAM_DRAW, ShaderCommon::PER_FRAME_UBO, 1, 0);
    m_lightingBuffer = new Buffer<ShaderCommon::LightingGL>(GL_UNIFORM_BUFFER, GL_STATIC_DRAW, ShaderCommon::LIGHTING_UBO, 1, 0);

    // Create samplers
    glGenSamplers(1, &m_nearestSampler);
    setSamplerParams(m_nearestSampler, GL_CLAMP_TO_EDGE, GL_NEAREST, GL_NEAREST);
    glGenSamplers(1, &m_linearSampler);
    setSamplerParams(m_linearSampler, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR);

    // Load shaders
	m_basicShader = new Shader("data/shaders/basic.vert", "data/shaders/basic.frag");
	m_noiseShader = new Shader("data/shaders/noise.vert", "data/shaders/basic.frag");
	m_floorShader = new Shader("data/shaders/basic.vert", "data/shaders/floor.frag");
	m_instancedShader = new Shader("data/shaders/instanced.vert", "data/shaders/shadeless.frag");
	m_finalOutputShader = new Shader("data/shaders/fullScreen.vert", "data/shaders/finalOutput.frag");
	m_backgroundShader = new Shader("data/shaders/fullScreen.vert", "data/shaders/background.frag");
	m_bloomShader = new Shader("data/shaders/fullScreen.vert", "data/shaders/bloom.frag");
	m_blurShaders[0] = new Shader("data/shaders/fullScreen.vert", "data/shaders/gaussianBlurX.frag");
	m_blurShaders[1] = new Shader("data/shaders/fullScreen.vert", "data/shaders/gaussianBlurY.frag");

	// Full screen quad
	m_fullScreenQuad = new FullScreenQuad();

	// Create FBO
	uint windowWidth = Globals::m_uiManager->m_screenWidth;
	uint windowHeight = Globals::m_uiManager->m_screenHeight;

	glActiveTexture(GL_TEXTURE0 + ShaderCommon::NON_USED_TEXTURE_BINDING);

	// Create color textures
	glGenTextures(1, &m_colorTexture);
	glBindTexture(GL_TEXTURE_2D, m_colorTexture);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, windowWidth, windowHeight);
	setTextureParams(GL_TEXTURE_2D, GL_CLAMP_TO_EDGE, GL_NEAREST, GL_NEAREST, 1);

	// Create depth texture
	glGenTextures(1, &m_depthTexture);
	glBindTexture(GL_TEXTURE_2D, m_depthTexture);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, windowWidth, windowHeight);
	setTextureParams(GL_TEXTURE_2D, GL_CLAMP_TO_EDGE, GL_NEAREST, GL_NEAREST, 1);

	// Create framebuffer textures
	m_fboAttachments[ShaderCommon::COLOR_FBO_BINDING] = GL_COLOR_ATTACHMENT0 + ShaderCommon::COLOR_FBO_BINDING;

	// Create fbo
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, m_fboAttachments[ShaderCommon::COLOR_FBO_BINDING], GL_TEXTURE_2D, m_colorTexture, 0);
	glDrawBuffers(ShaderCommon::NUM_FBO_BINDINGS, m_fboAttachments);

	// Bloom textures
	m_bloomSizeX = windowWidth >> 1;
	m_bloomSizeY = windowHeight >> 1;
	glGenTextures(2, m_bloomTextures);
	for (uint i = 0; i < 2; i++)
	{
		glBindTexture(GL_TEXTURE_2D, m_bloomTextures[i]);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, m_bloomSizeX, m_bloomSizeY);
		setTextureParams(GL_TEXTURE_2D, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR, 1);
	}

	// Bloom FBOs
	glGenFramebuffers(2, m_bloomFBOs);
	for (uint i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_bloomFBOs[i]);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_bloomTextures[i], 0);
		GLenum bloomFBOAttachments[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, bloomFBOAttachments);
	}

	// Background texture
	m_backgroundSizeX = windowWidth >> 1;
	m_backgroundSizeY = windowHeight >> 1;
	glGenTextures(1, &m_backgroundTexture);
	glBindTexture(GL_TEXTURE_2D, m_backgroundTexture);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, m_backgroundSizeX, m_backgroundSizeY);
	setTextureParams(GL_TEXTURE_2D, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR, 1);

	// Background FBO
	glGenFramebuffers(1, &m_backgroundFBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_backgroundFBO);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_backgroundTexture, 0);
	GLenum backgroundFBOAttachments[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, backgroundFBOAttachments);
}

RenderManager::~RenderManager()
{
	glDeleteSamplers(1, &m_nearestSampler);
	glDeleteSamplers(1, &m_linearSampler);


    delete m_materialBuffer;
    delete m_transformBuffer;
    delete m_perFrameBuffer;
    delete m_lightingBuffer;
}

void RenderManager::resizeWindow(int width, int height)
{
	// Nothing
}

void RenderManager::render()
{
	bool bloomEnabled = false;
    
    uint screenWidth = Globals::m_uiManager->m_screenWidth;
    uint screenHeight = Globals::m_uiManager->m_screenHeight;
    float aspectRatio = (float)screenWidth / screenHeight;

	Camera* camera = Globals::m_shmupGame->m_camera;
    glm::vec3 cameraPos = camera->getPosition();
    float fov = glm::radians(camera->m_fov);
    m_viewMatrix = camera->getViewMatrix();
    m_projMatrix = glm::perspective(fov, aspectRatio, 1.0f, 100.0f);
	//float orthoSizeX = ShmupGame::WORLD_BOUND_X;
	//float orthoSizeY = ShmupGame::WORLD_BOUND_Y;
	//m_projMatrix = glm::ortho(-orthoSizeX, orthoSizeX, -orthoSizeY, orthoSizeY, 0.1f, 1000.0f);
    glm::mat4 viewProjectionMatrix = m_projMatrix * m_viewMatrix;

	// Get background color
	glm::vec3 backgroundColor = glm::vec3(1.0, 0.0, 0.0);

    // Update the per frame buffer
    ShaderCommon::PerFrameGL perFrame;
    perFrame.cameraPos = cameraPos;
    perFrame.viewProjection = viewProjectionMatrix;
	perFrame.invScreenSize = 1.0f / glm::vec2(screenWidth, screenHeight);
	perFrame.invBackgroundSize = 1.0f / glm::vec2(m_backgroundSizeX, m_backgroundSizeY);
	perFrame.invBlurSize = 1.0f / glm::vec2(m_bloomSizeX, m_bloomSizeY);
	perFrame.time = Globals::m_uiManager->getTime();
	perFrame.backgroundColor = backgroundColor;
    m_perFrameBuffer->updateAll(&perFrame);

    // Update lighting buffer
    if (m_lightBufferDirty)
    {
        ShaderCommon::LightingGL lighting;

        uint numDirLights = Globals::m_shmupGame->m_dirLights.size();
        uint numPointLights = Globals::m_shmupGame->m_pointLights.size();
        lighting.numDirLights = numDirLights;
        lighting.numPointLights = numPointLights;

        // Dir lights
        uint i = 0;
        for (auto& dirLight : Globals::m_shmupGame->m_dirLights)
        {
            lighting.dirLights[i].color = dirLight->m_color;
            lighting.dirLights[i].direction = dirLight->getDirection();
            i++;
        }

        // Point lights
        i = 0;
        for (auto& pointLight : Globals::m_shmupGame->m_pointLights)
        {
            float radius = pointLight->m_radius;
            float attenuation = 1.0f / (radius * radius);
            glm::vec3 position = pointLight->getPosition();

            lighting.pointLights[i].color = pointLight->m_color;
            lighting.pointLights[i].position = glm::vec4(position, attenuation);
        }
        m_lightingBuffer->updateAll(&lighting);

		//m_lightBufferDirty = false;
    }

	// Render half-size background
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_backgroundFBO);
	setViewportSize(m_backgroundSizeX, m_backgroundSizeY);
	setRenderState(RENDER_STATE::COLOR);
	m_backgroundShader->render();
	m_fullScreenQuad->render();
	glActiveTexture(GL_TEXTURE0 + ShaderCommon::BACKGROUND_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, m_backgroundTexture);

	// Render background to screen
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_defaultFBO);
	setViewportSize(screenWidth, screenHeight);
	setRenderState(RENDER_STATE::COLOR);
	m_finalOutputShader->render();
	m_fullScreenQuad->render();

	// Clear depth
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_defaultFBO);
	setRenderState(RENDER_STATE::DEPTH_WRITE);
	setViewportSize(screenWidth, screenHeight);
	clearDepth();	
    
    // Render scene
    setRenderState(RENDER_STATE::COLOR | RENDER_STATE::CULLING | RENDER_STATE::DEPTH_TEST | RENDER_STATE::DEPTH_WRITE);
    
	m_basicShader->render();
    for (auto& entity : m_entities)
    {
        entity->render();
    }
	
	m_noiseShader->render();
	for (auto& entity : m_noiseEntities)
	{
		entity->render();
	}
	
	m_instancedShader->render();
	for (auto& objectPool : m_objectPools)
	{
		objectPool->render();
	}

	if (bloomEnabled)
	{
		glActiveTexture(GL_TEXTURE0 + ShaderCommon::BLUR_TEXTURE);
		setViewportSize(m_bloomSizeX, m_bloomSizeY);
		setRenderState(RENDER_STATE::COLOR | RENDER_STATE::LINEAR_SAMPLING_COLOR);

		// Blur color texture into first bloom texture
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_bloomFBOs[0]);
		glBindTexture(GL_TEXTURE_2D, m_colorTexture);
		m_blurShaders[0]->render();
		m_fullScreenQuad->render();

		// Blur first bloom texture into second bloom texture
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_bloomFBOs[1]);
		glBindTexture(GL_TEXTURE_2D, m_bloomTextures[0]);
		m_blurShaders[1]->render();
		m_fullScreenQuad->render();
	}

	
}

void RenderManager::renderMaterial(const ShaderCommon::MaterialGL& material)
{
    m_materialBuffer->updateAll(&material);
}

void RenderManager::renderTransform(const ShaderCommon::TransformGL& transform)
{
    m_transformBuffer->updateAll(&transform);
}


void RenderManager::addObjectPool(ObjectPool* objectPool)
{
	m_objectPools.push_back(objectPool);
}

void RenderManager::removeObjectPool(ObjectPool* objectPool)
{
	m_objectPools.remove(objectPool);
}

void RenderManager::addEntity(Entity* entity)
{
	if (entity->m_render->m_materials[0]->m_noiseStrength > 0.001f)
	{
		m_noiseEntities.push_back(entity);
	}
	else
	{
		m_entities.push_back(entity);
	}
}

void RenderManager::removeEntity(Entity* entity)
{
	if (entity->m_render->m_materials[0]->m_noiseStrength > 0.001f)
	{
		m_noiseEntities.remove(entity);
	}
	else
	{
		m_entities.remove(entity);
	}
}

void RenderManager::setFloor(Entity* floor)
{
	removeEntity(floor);
	m_floor = floor;
}

void RenderManager::setRenderState(uint renderStateBitfield)
{
    // Culling
    if (Utils::checkBitfield(renderStateBitfield, RENDER_STATE::CULLING))
        glEnable(GL_CULL_FACE);
    else glDisable(GL_CULL_FACE);

    // Depth test
    if (Utils::checkBitfield(renderStateBitfield, RENDER_STATE::DEPTH_TEST))
        glEnable(GL_DEPTH_TEST);
    else glDisable(GL_DEPTH_TEST);

    // Depth write (if depthTest is disabled, depthWrite will automatically be disabled)
    if (Utils::checkBitfield(renderStateBitfield, RENDER_STATE::DEPTH_WRITE))
        glDepthMask(GL_TRUE);
    else glDepthMask(GL_FALSE);

    // Render to color buffer
    if (Utils::checkBitfield(renderStateBitfield, RENDER_STATE::COLOR))
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    else glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

    // Alpha blending
    if (Utils::checkBitfield(renderStateBitfield, RENDER_STATE::ALPHA_BLEND))
    {
        //glEnablei(GL_BLEND, ShaderGlobals::COLOR_FBO_BINDING);
        glEnable(GL_BLEND);
        glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
    }
    else glDisable(GL_BLEND);

    
    // sRGB conversion when writing to color buffer
    #if defined(OS_WINDOWS)
        if (Utils::checkBitfield(renderStateBitfield, RENDER_STATE::FRAMEBUFFER_SRGB))
            glEnable(GL_FRAMEBUFFER_SRGB);
        else glDisable(GL_FRAMEBUFFER_SRGB);
    #endif

    // Linear vs. Nearest sampling for FBO color texture
    if (Utils::checkBitfield(renderStateBitfield, RENDER_STATE::LINEAR_SAMPLING_COLOR))
        glBindSampler(ShaderCommon::COLOR_FBO_TEXTURE, m_linearSampler);
    else glBindSampler(ShaderCommon::COLOR_FBO_TEXTURE, m_nearestSampler);

    // Stencil (stencil value is embedded in the lower 16 bits of the bitfield)
    uint stencilValue = renderStateBitfield & 0xFFFF;
    if (Utils::checkBitfield(renderStateBitfield, RENDER_STATE::STENCIL_WRITE))
    {
        // When fragment passes depth test, replace stencil value with 0xFF,
        // which is then masked to place 1 in the 'bitMask' bit
        glEnable(GL_STENCIL_TEST);
        glStencilMask(stencilValue);
        glStencilFunc(GL_ALWAYS, 0xFF, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    }
    else if (Utils::checkBitfield(renderStateBitfield, RENDER_STATE::STENCIL_TEST))
    {
        // Fragment passes stencil test if the stencil buffer value ANDed with the transparent bit
        // equals 0xFF ANDed with the transparent bit, meaning both bits are 1.
        // No modifaction is made to the stencil buffer, but a failure means the fragment is not processed
        glEnable(GL_STENCIL_TEST);
        glStencilMask(0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        glStencilFunc(GL_EQUAL, 0xFF, stencilValue);
    }
    else
    {
        glDisable(GL_STENCIL_TEST);
    }
}

void RenderManager::setViewportSize(uint width, uint height)
{
    glViewport(0, 0, width, height);
}

void RenderManager::clearColor(int index, const glm::vec4& color)
{
    glClearBufferfv(GL_COLOR, index, &color[0]);
}

void RenderManager::clearDepth()
{
    float clearDepth = 1.0f;
    glClearBufferfv(GL_DEPTH, 0, &clearDepth);
}

void RenderManager::clearDepthStencil()
{
    float clearDepth = 1.0f;
    int clearStencil = 0x00;
    glClearBufferfi(GL_DEPTH_STENCIL, 0, clearDepth, clearStencil);
}

void RenderManager::setTextureParams(GLenum target, GLenum wrapMode, GLenum minFilter, GLenum magFilter, uint numLevels)
{
    glTexParameteri(target, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, wrapMode);
    glTexParameteri(target, GL_TEXTURE_WRAP_R, wrapMode);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, magFilter);
    glTexParameteri(target, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, numLevels - 1);
}

void RenderManager::setSamplerParams(GLuint sampler, GLenum wrapMode, GLenum minFilter, GLenum magFilter)
{
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, wrapMode);
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, wrapMode);
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_R, wrapMode);
    glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, minFilter);
    glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, magFilter);
}
