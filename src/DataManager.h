#pragma once

#include <string>
#include <map>
#include <glm/glm.hpp>
#include "Common.h"
#include "Game/StateMachine.h"

class Material;
class Mesh;

class DataManager
{
public:

    DataManager();
    ~DataManager();

    GLuint loadTexture(void* data, const glm::uvec2& dimensions, const std::string& name);
    GLuint loadShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);

    GLuint getTexture(const std::string& name);
    Material* getMaterial(const std::string& name);
	Material* getMaterial(COLOR color);
    Mesh* getMesh(const std::string& name);

private:

    GLuint createShader(GLenum Type, const std::string& filename);
    bool checkProgram(GLuint ProgramName);
    bool checkShader(GLuint ShaderName);

    std::string m_shaderHeader;

    std::map<std::string, GLuint> m_textures;
    std::map<std::string, Material*> m_materials;
    std::map<std::string, Mesh*> m_meshes;
};
