#include "Utils.h"

#include <sstream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Globals.h"
#include "UIManager.h"
#include "GameManager.h"
#include "RenderManager.h"
#include "Camera.h"

namespace Utils
{
    bool checkBitfield(uint renderStateBitfield, uint renderStateEnum)
    {
        return (renderStateBitfield & renderStateEnum) > 0;
    }

    glm::vec2 parseVec2(const std::string& vecString)
    {
        glm::vec2 result;
        std::vector<std::string> pieces = parseSpaceSeparatedString(vecString);
        result.x = (float)std::atof(pieces[0].c_str());
        result.y = (float)std::atof(pieces[1].c_str());
        return result;
    }


    glm::vec3 parseVec3(const std::string& vecString)
    {
        glm::vec3 result;
        std::vector<std::string> pieces = parseSpaceSeparatedString(vecString);
        result.x = (float)std::atof(pieces[0].c_str());
        result.y = (float)std::atof(pieces[1].c_str());
        result.z = (float)std::atof(pieces[2].c_str());
        return result;
    }

    glm::vec4 parseVec4(const std::string& vecString)
    {
        glm::vec4 result;
        std::vector<std::string>& pieces = parseSpaceSeparatedString(vecString);
        result.x = (float)std::atof(pieces[0].c_str());
        result.y = (float)std::atof(pieces[1].c_str());
        result.z = (float)std::atof(pieces[2].c_str());
        result.w = (float)std::atof(pieces[3].c_str());
        return result;
    }

    glm::quat parseQuat(const std::string& quatString)
    {
        std::vector<std::string>& pieces = parseSpaceSeparatedString(quatString);
        float x = (float)std::atof(pieces[0].c_str());
        float y = (float)std::atof(pieces[1].c_str());
        float z = (float)std::atof(pieces[2].c_str());
        float w = (float)std::atof(pieces[3].c_str());
        return glm::quat(w, x, y, z);
    }
    glm::mat4 parseMat4(const std::string& matrixString)
    {
        // Input string is in ROW ORDER. Meaning the first 4 floats are the first row, not the first column
        glm::mat4 result;
        std::vector<std::string>& pieces = parseSpaceSeparatedString(matrixString);

        result[0].x = (float)std::atof(pieces[0].c_str());
        result[1].x = (float)std::atof(pieces[1].c_str());
        result[2].x = (float)std::atof(pieces[2].c_str());
        result[3].x = (float)std::atof(pieces[3].c_str());

        result[0].y = (float)std::atof(pieces[4].c_str());
        result[1].y = (float)std::atof(pieces[5].c_str());
        result[2].y = (float)std::atof(pieces[6].c_str());
        result[3].y = (float)std::atof(pieces[7].c_str());

        result[0].z = (float)std::atof(pieces[8].c_str());
        result[1].z = (float)std::atof(pieces[9].c_str());
        result[2].z = (float)std::atof(pieces[10].c_str());
        result[3].z = (float)std::atof(pieces[11].c_str());

        result[0].w = (float)std::atof(pieces[12].c_str());
        result[1].w = (float)std::atof(pieces[13].c_str());
        result[2].w = (float)std::atof(pieces[14].c_str());
        result[3].w = (float)std::atof(pieces[15].c_str());

        return result;
    }

    std::vector<std::string> parseSpaceSeparatedString(const std::string& configData)
    {
        std::vector<std::string> tokens;
        std::istringstream iss(configData);
        std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter<std::vector<std::string>>(tokens));
        return tokens;
    }

    std::vector<glm::vec3> parseVec3s(const std::string& data, uint count)
    {
        std::vector<glm::vec3> vec3s(count);
        std::vector<std::string>& pieces = parseSpaceSeparatedString(data);
        for (uint i = 0; i < pieces.size()/3; i++)
        {
            float x = (float)std::atof(pieces[i*3+0].c_str());
            float y = (float)std::atof(pieces[i*3+1].c_str());
            float z = (float)std::atof(pieces[i*3+2].c_str());
            vec3s[i] = glm::vec3(x, y, z);
        }
        return vec3s;
    }

    std::vector<float> parseFloats(const std::string& data, uint count)
    {
        std::vector<float> floats(count);
        std::vector<std::string>& pieces = parseSpaceSeparatedString(data);
        for (uint i = 0; i < pieces.size(); i++)
        {
            floats[i] = (float)std::atof(pieces[i].c_str());
        }
        return floats;
    }

    std::vector<glm::quat> parseQuats(const std::string& data, uint count)
    {
        std::vector<glm::quat> quats(count);
        std::vector<std::string>& pieces = parseSpaceSeparatedString(data);
        for (uint i = 0; i < pieces.size() / 4; i++)
        {
            float x = (float)std::atof(pieces[i * 4 + 0].c_str());
            float y = (float)std::atof(pieces[i * 4 + 1].c_str());
            float z = (float)std::atof(pieces[i * 4 + 2].c_str());
            float w = (float)std::atof(pieces[i * 4 + 3].c_str());
            quats[i] = glm::quat(w, x, y, z);
        }
        return quats;
    }

    std::string loadFile(const std::string& filename)
    {
        std::ifstream stream(filename.c_str(), std::ios::in);
        return std::string(std::istreambuf_iterator<char>(stream),
            std::istreambuf_iterator<char>());
    }

    std::string getNameFromFilename(const std::string& filename)
    {
        uint start = (uint)(filename.find_last_of("/") + 1);
        uint end = (uint)(filename.find_last_of("."));
        std::string name = filename.substr(start, end - start);
        return name;
    }

    Ray getPickingRay()
    {
        UIManager* uiManager = Globals::m_uiManager;
    
        uint mouseX = Globals::m_uiManager->m_mouseX;
        uint mouseY = Globals::m_uiManager->m_mouseY;
        uint screenWidth = Globals::m_uiManager->m_screenWidth;
        uint screenHeight = Globals::m_uiManager->m_screenHeight;
        glm::mat4 viewMatrix = Globals::m_renderManager->m_viewMatrix;
        glm::mat4 projMatrix = Globals::m_renderManager->m_projMatrix;

    
        glm::vec4 viewport(0.0f, 0.0f, screenWidth, screenHeight);
        glm::vec3 windowPosClose(mouseX, mouseY, 0.0f);
        glm::vec3 windowPosFar(mouseX, mouseY, 1.0f);

        glm::vec3 nearPlanePoint = glm::unProject(windowPosClose, viewMatrix, projMatrix, viewport);
        glm::vec3 farPlanePoint = glm::unProject(windowPosFar, viewMatrix, projMatrix, viewport);

        glm::vec3 position = nearPlanePoint;
        glm::vec3 direction = glm::normalize(farPlanePoint - nearPlanePoint);
        Ray r(position, direction);
        return r;
    }


}


Ray::Ray(const glm::vec3& position, const glm::vec3& direction) :
    m_position(position),
    m_direction(direction)
{

}
