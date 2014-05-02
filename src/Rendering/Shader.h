#pragma once

#include <string>
#include "Common.h"

class Shader
{
public:
	
	Shader(const std::string& vertexShader, const std::string& fragmentShader);
	~Shader();
	void render();

	GLuint m_program;
	
	GLint m_diffuseTextureBinding;
	GLint m_reflectTextureBinding;
	GLint m_specularTextureBinding;
	GLint m_normalTextureBinding;
	GLint m_colorFBOTextureBinding;
	GLint m_bloomTextureBinding;
	GLint m_blurTextureBinding;
	GLint m_backgroundTextureBinding;
};