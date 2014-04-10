#include "DataManager.h"

#include "Utils.h"
#include "Mesh.h"
#include "ShaderCommon.h"
#include "Globals.h"
#include "RenderManager.h"
#include "Material.h"

DataManager::DataManager()
{
    // Create cube primitive
    float vertices[192] = { -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.5f, 0.5f, -0.5f, 1.0f, 0.0f, -0.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, -0.0f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, -0.0f, 1.0f, 1.0f, 0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f };
    ushort indices[36] = { 0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23 };
    Mesh* cubeMesh = new Mesh(vertices, indices, 24, 36, { 0 });
    m_meshes["cube"] = cubeMesh;

	Material* greenMaterial = new Material();
	greenMaterial->m_diffuseColor = glm::vec4(0, 1, 0, 1);
	m_materials["green"] = greenMaterial;

	Material* redMaterial = new Material();
	redMaterial->m_diffuseColor = glm::vec4(1, 0, 0, 1);
	m_materials["red"] = redMaterial;

	Material* blueMaterial = new Material();
	blueMaterial->m_diffuseColor = glm::vec4(0, 0, 1, 1);
	m_materials["blue"] = blueMaterial;


    m_shaderHeader = Utils::loadFile("data/shaders/globals");
}

DataManager::~DataManager()
{
	for (auto& texture : m_textures)
	{
		glDeleteTextures(1, &texture.second);
	}

	m_meshes.clear();

	for (auto& material : m_materials)
	{
		delete material.second;
	}

	m_materials.clear();

	for (auto& mesh : m_meshes)
	{
		delete mesh.second;
	}

	m_meshes.clear();
}

GLuint DataManager::loadTexture(void* data, const glm::uvec2& dimensions, const std::string& name)
{
    // Return if it was loaded already
    auto& foundTexture = m_textures.find(name);
    if (foundTexture != m_textures.end())
        return foundTexture->second;

    // Create texture, set OpenGL params
    GLuint texture;
    glActiveTexture(GL_TEXTURE0 + ShaderCommon::NON_USED_TEXTURE_BINDING);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    Globals::m_renderManager->setTextureParams(GL_TEXTURE_2D, GL_REPEAT, GL_LINEAR, GL_LINEAR, 1);

    // Create storage
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, dimensions.x, dimensions.y);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, dimensions.x, dimensions.y, GL_RGB, GL_UNSIGNED_BYTE, data);

    m_textures[name] = texture;
    return texture;
}

GLuint DataManager::getTexture(const std::string& name)
{
    auto& foundTexture = m_textures.find(name);
    if (foundTexture != m_textures.end())
        return foundTexture->second;
    else
        return 0;
}

Material* DataManager::getMaterial(const std::string& name)
{
    auto& foundMaterial = m_materials.find(name);
    if (foundMaterial != m_materials.end())
        return foundMaterial->second;
    else
        return 0;
}

Mesh* DataManager::getMesh(const std::string& name)
{
    auto& foundMesh = m_meshes.find(name);
    if (foundMesh != m_meshes.end())
        return foundMesh->second;
    else
        return 0;
}


GLuint DataManager::loadShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLuint vertexShaderObject = createShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fragmentShaderObject = createShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderObject);
    glAttachShader(shaderProgram, fragmentShaderObject);
    glDeleteShader(vertexShaderObject);
    glDeleteShader(fragmentShaderObject);

    glLinkProgram(shaderProgram);
    checkProgram(shaderProgram);

    return shaderProgram;
}

GLuint DataManager::createShader(GLenum Type, const std::string& filename)
{
    std::string shaderSource = m_shaderHeader + Utils::loadFile(filename);
    const char* shaderSourceC = shaderSource.c_str();
    GLuint shader = glCreateShader(Type);
    glShaderSource(shader, 1, &shaderSourceC, 0);
    glCompileShader(shader);
    checkShader(shader);
    return shader;
}

bool DataManager::checkProgram(GLuint ProgramName)
{
    if (!ProgramName)
        return false;

    GLint Result = GL_FALSE;
    glGetProgramiv(ProgramName, GL_LINK_STATUS, &Result);

    int InfoLogLength;
    glGetProgramiv(ProgramName, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> Buffer(glm::max(InfoLogLength, int(1)));
        glGetProgramInfoLog(ProgramName, InfoLogLength, NULL, &Buffer[0]);
        fprintf(stdout, "%s\n", &Buffer[0]);
    }

    return Result == GL_TRUE;
}

bool DataManager::checkShader(GLuint ShaderName)
{
    if (!ShaderName)
        return false;

    GLint Result = GL_FALSE;
    glGetShaderiv(ShaderName, GL_COMPILE_STATUS, &Result);

    int InfoLogLength;
    glGetShaderiv(ShaderName, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> Buffer(InfoLogLength);
        glGetShaderInfoLog(ShaderName, InfoLogLength, NULL, &Buffer[0]);
        fprintf(stdout, "%s\n", &Buffer[0]);
    }

    return Result == GL_TRUE;
}
