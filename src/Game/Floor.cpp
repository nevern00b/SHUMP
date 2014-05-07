#include "Floor.h"

#include <glm/gtc/matrix_transform.hpp>
#include "Globals.h"

Floor::Floor()
{
	m_positions[0] = glm::vec3(-60.0f, 0.0f, 0.0f);
	m_positions[1] = glm::vec3(60.0f, 0.0f, 0.0f);
	m_positions[2] = glm::vec3(60.0f, 200.0f, 0.0f);
	m_positions[3] = glm::vec3(-60.0f, 200.0f, 0.0f);
}

Floor::~Floor()
{

}

glm::mat4 Floor::getShadowMatrix()
{
	glm::mat4 shadowMat;
	glm::vec4 lightpos(0.0f, -0.5f, 1.0f, 0.0f);
	glm::vec4 groundplane = glm::vec4(0.0f, 0.0f, 1.0f, 2.0f);

	/* Find dot product between light position vector and ground plane normal. */
	float dot = groundplane.x * lightpos.x +
				groundplane.y * lightpos.y +
				groundplane.z * lightpos.z +
				groundplane.w * lightpos.w;

	shadowMat[0][0] = dot - lightpos.x * groundplane.x;
	shadowMat[1][0] = 0.f - lightpos.x * groundplane.y;
	shadowMat[2][0] = 0.f - lightpos.x * groundplane.z;
	shadowMat[3][0] = 0.f - lightpos.x * groundplane.w;

	shadowMat[0][1] = 0.f - lightpos.y * groundplane.x;
	shadowMat[1][1] = dot - lightpos.y * groundplane.y;
	shadowMat[2][1] = 0.f - lightpos.y * groundplane.z;
	shadowMat[3][1] = 0.f - lightpos.y * groundplane.w;

	shadowMat[0][2] = 0.f - lightpos.z * groundplane.x;
	shadowMat[1][2] = 0.f - lightpos.z * groundplane.y;
	shadowMat[2][2] = dot - lightpos.z * groundplane.z;
	shadowMat[3][2] = 0.f - lightpos.z * groundplane.w;

	shadowMat[0][3] = 0.f - lightpos.w * groundplane.x;
	shadowMat[1][3] = 0.f - lightpos.w * groundplane.y;
	shadowMat[2][3] = 0.f - lightpos.w * groundplane.z;
	shadowMat[3][3] = dot - lightpos.w * groundplane.w;

	//shadowMat[3][3] = 400.0f;
	//shadowMat = glm::transpose(shadowMat);


	//shadowMat = glm::mat4(1.0);
	//shadowMat[2][2] = 0;
	//shadowMat[0][2] = -lightpos.x / lightpos.z;
	//shadowMat[1][2] = -lightpos.y / lightpos.z;

	return shadowMat;
}