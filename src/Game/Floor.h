#pragma once

#include "Common.h"
#include <glm/glm.hpp>

class Floor
{
public:
	Floor();
	virtual ~Floor();
	glm::mat4 getShadowMatrix();

private:
	
	glm::vec3 m_positions[4];
};