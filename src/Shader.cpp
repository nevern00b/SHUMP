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
}