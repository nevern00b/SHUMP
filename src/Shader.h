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
	
	GLuint m_diffuseTextureBinding;
	GLuint m_reflectTextureBinding;
	GLuint m_specularTextureBinding;
	GLuint m_normalTextureBinding;
};