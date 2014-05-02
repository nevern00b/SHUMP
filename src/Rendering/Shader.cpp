#include "Shader.h"

#include "Globals.h"
#include "RenderManager.h"
#include "DataManager.h"
#include "ShaderCommon.h"

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
{
	m_program = Globals::m_dataManager->loadShaderProgram(vertexShader, fragmentShader);

	//m_positionAttrBinding = glGetAttribLocation(m_program, "aPosition");
	//m_normalAttrBinding = glGetAttribLocation(m_program, "aNormal");
	//m_uvAttrBinding = glGetAttribLocation(m_program, "aUV");

	m_diffuseTextureBinding = glGetUniformLocation(m_program, "tDiffuse");
	m_reflectTextureBinding = glGetUniformLocation(m_program, "tReflect");
	m_specularTextureBinding = glGetUniformLocation(m_program, "tSpecular");
	m_normalTextureBinding = glGetUniformLocation(m_program, "tNormal");
	m_colorFBOTextureBinding = glGetUniformLocation(m_program, "tColor");
	m_bloomTextureBinding = glGetUniformLocation(m_program, "tBloom");
	m_blurTextureBinding = glGetUniformLocation(m_program, "tBlur");
	m_backgroundTextureBinding = glGetUniformLocation(m_program, "tBackground");

	uint perFrameUBOBinding = glGetUniformBlockIndex(m_program, "PerFrameUBO");
	glUniformBlockBinding(m_program, perFrameUBOBinding, ShaderCommon::PER_FRAME_UBO);

	uint transformUBOBinding = glGetUniformBlockIndex(m_program, "TransformUBO");
	glUniformBlockBinding(m_program, transformUBOBinding, ShaderCommon::TRANSFORM_UBO);

	uint materialUBOBinding = glGetUniformBlockIndex(m_program, "MaterialUBO");
	glUniformBlockBinding(m_program, materialUBOBinding, ShaderCommon::MATERIAL_UBO);
	
	uint lightingUBOBinding = glGetUniformBlockIndex(m_program, "LightingUBO");
	glUniformBlockBinding(m_program, lightingUBOBinding, ShaderCommon::LIGHTING_UBO);

}

Shader::~Shader()
{
	glDeleteProgram(m_program);
}


void Shader::render()
{
	if (Globals::m_renderManager->m_activeShader == this) return; // Don't call if its already active
	Globals::m_renderManager->m_activeShader = this;
	glUseProgram(m_program);

	// Bind textures to the shader
	glUniform1i(m_diffuseTextureBinding, ShaderCommon::DIFFUSE_TEXTURE);
	glUniform1i(m_normalTextureBinding, ShaderCommon::NORMAL_TEXTURE);
	glUniform1i(m_specularTextureBinding, ShaderCommon::SPECULAR_TEXTURE);
	glUniform1i(m_reflectTextureBinding, ShaderCommon::REFLECT_TEXTURE);
	glUniform1i(m_colorFBOTextureBinding, ShaderCommon::COLOR_FBO_TEXTURE);
	glUniform1i(m_bloomTextureBinding, ShaderCommon::BLOOM_TEXTURE);
	glUniform1i(m_blurTextureBinding, ShaderCommon::BLUR_TEXTURE);
	glUniform1i(m_backgroundTextureBinding, ShaderCommon::BACKGROUND_TEXTURE);


	Globals::m_renderManager->m_materialBuffer->bindToShader();
	Globals::m_renderManager->m_transformBuffer->bindToShader();
	Globals::m_renderManager->m_perFrameBuffer->bindToShader();
	Globals::m_renderManager->m_lightingBuffer->bindToShader();
}