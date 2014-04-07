#pragma once

#include <glm/glm.hpp>
#include "Common.h"

namespace ShaderCommon
{
    // Max values
    const uint MAX_DIR_LIGHTS                       = 8;
    const uint MAX_POINT_LIGHTS                     = 8;
    const uint MAX_BONES                            = 50;

    // Texture binding points                                
    const uint DIFFUSE_TEXTURE                      = 0;
    const uint NORMAL_TEXTURE                       = 1;
    const uint SPECULAR_TEXTURE                     = 2;
    const uint REFLECT_TEXTURE                      = 3;
    const uint SKYBOX_TEXTURE                       = 4;
    const uint COLOR_FBO_TEXTURE_BINDING            = 5;
    const uint NON_USED_TEXTURE_BINDING             = 6; // Used for modifying textures that shouldn't be bound to a binding point

    // Vertex attribute indexes                                     
    const uint POSITION_ATTR                        = 0;
    const uint NORMAL_ATTR                          = 1;
    const uint UV_ATTR                              = 2;
    const uint BONE_WEIGHTS_ATTR                    = 3;
    const uint BONE_IDS_ATTR                        = 4;

    // FBO binding points                                            
    const uint DEFAULT_FRAMEBUFFER                  = 0;
    const uint COLOR_FBO_BINDING                    = 0;
    const uint NORMAL_FBO_BINDING                   = 1;
    const uint MOTION_BLUR_FBO_BINDING              = 2;
    const uint NUM_FBO_BINDINGS                     = 3;

    // Uniform buffer binding points                        
    const uint PER_FRAME_UBO                        = 0;
    const uint LIGHTING_UBO                         = 1;
    const uint MATERIAL_UBO                         = 2;
    const uint TRANSFORM_UBO                        = 3;

    struct PerFrameGL
    {
        glm::mat4 viewProjection;
        glm::mat4 skyboxMVP;
        glm::vec3 cameraPos;
    };

    struct MaterialGL
    {
        glm::vec4 diffuseColor;
        float diffuseBlend;
        float reflectBlend;
        float specIntensity;
        float specPower;
        float specBlend;
        float normalIntensity;
    };

    struct TransformGL
    {
        glm::mat4 modelMatrix;
    };

    struct DirLightGL
    {
        glm::vec3 color;
        float pad1;
        glm::vec3 direction;
        float pad2;
    };

    struct PointLightGL
    {
        glm::vec3 color;
        float pad;
        glm::vec4 position; //position.w contains attenuation factor
    };

    struct LightingGL
    {
        PointLightGL pointLights[MAX_POINT_LIGHTS];
        DirLightGL dirLights[MAX_DIR_LIGHTS];
        int numPointLights;
        int numDirLights;
        float padding[2];
    };
}

