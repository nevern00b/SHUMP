#include "RenderManager.h"

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

RenderManager::RenderManager() :
    m_lightBufferDirty(false)
{
    // Init GL state
    glClearColor(1, 1, 1, 1);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);

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
    m_basicShader = Globals::m_dataManager->loadShaderProgram("data/shaders/basic.vert", "data/shaders/basic.frag");
}

RenderManager::~RenderManager()
{
    delete m_materialBuffer;
    delete m_transformBuffer;
    delete m_perFrameBuffer;
    delete m_lightingBuffer;
}

void RenderManager::render()
{
    uint screenWidth = Globals::m_uiManager->m_screenWidth;
    uint screenHeight = Globals::m_uiManager->m_screenHeight;
    float aspectRatio = (float)screenWidth / screenHeight;

    Camera* camera = Globals::m_gameManager->m_camera;
    glm::vec3 cameraPos = camera->getPosition();
    float fov = glm::radians(camera->m_fov);
    m_viewMatrix = camera->getViewMatrix();
    //m_projMatrix = glm::perspective(fov, aspectRatio, 0.1f, 1000.0f);
    float orthoSize = 10.0f;
    m_projMatrix = glm::ortho(-orthoSize*aspectRatio, orthoSize*aspectRatio, -orthoSize, orthoSize, 0.1f, 1000.0f);
    glm::mat4 viewProjectionMatrix = m_projMatrix * m_viewMatrix;

    // Update the per frame buffer
    ShaderCommon::PerFrameGL perFrame;
    perFrame.cameraPos = cameraPos;
    perFrame.viewProjection = viewProjectionMatrix;
    m_perFrameBuffer->updateAll(&perFrame);

    // Update lighting buffer
    if (m_lightBufferDirty)
    {
        ShaderCommon::LightingGL lighting;

        uint numDirLights = Globals::m_gameManager->m_dirLights.size();
        uint numPointLights = Globals::m_gameManager->m_pointLights.size();
        lighting.numDirLights = numDirLights;
        lighting.numPointLights = numPointLights;

        // Dir lights
        uint i = 0;
        for (auto& dirLight : Globals::m_gameManager->m_dirLights)
        {
            lighting.dirLights[i].color = dirLight->m_color;
            lighting.dirLights[i].direction = dirLight->getDirection();
            i++;
        }

        // Point lights
        i = 0;
        for (auto& pointLight : Globals::m_gameManager->m_pointLights)
        {
            float radius = pointLight->m_radius;
            float attenuation = 1.0f / (radius * radius);
            glm::vec3 position = pointLight->getPosition();

            lighting.pointLights[i].color = pointLight->m_color;
            lighting.pointLights[i].position = glm::vec4(position, attenuation);
        }
        m_lightingBuffer->updateAll(&lighting);
    }



    // Clear the framebuffer
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // 0 is default framebuffer
    setViewportSize(screenWidth, screenHeight);
    setRenderState(RENDER_STATE::DEPTH_WRITE | RENDER_STATE::COLOR);
    clearColor(0, glm::vec4(0, 0, 0, 0));
    clearDepth();

    // Render scene
    setRenderState(RENDER_STATE::COLOR | RENDER_STATE::CULLING | RENDER_STATE::DEPTH_TEST | RENDER_STATE::DEPTH_WRITE | RENDER_STATE::FRAMEBUFFER_SRGB);
    glUseProgram(m_basicShader);

    for (auto& entity : m_entities)
    {
        entity->render();
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


void RenderManager::addEntity(Entity* entity)
{
    m_entities.push_back(entity);
}

void RenderManager::removeEntity(Entity* entity)
{
    m_entities.remove(entity);
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
    if (Utils::checkBitfield(renderStateBitfield, RENDER_STATE::FRAMEBUFFER_SRGB))
        glEnable(GL_FRAMEBUFFER_SRGB);
    else glDisable(GL_FRAMEBUFFER_SRGB);

    // Linear vs. Nearest sampling for FBO color texture
    if (Utils::checkBitfield(renderStateBitfield, RENDER_STATE::LINEAR_SAMPLING_COLOR))
        glBindSampler(ShaderCommon::COLOR_FBO_TEXTURE_BINDING, m_linearSampler);
    else glBindSampler(ShaderCommon::COLOR_FBO_TEXTURE_BINDING, m_nearestSampler);

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
