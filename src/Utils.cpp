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

    std::string loadFile(const std::string& filename)
    {
        std::ifstream stream(filename.c_str(), std::ios::in);
        return std::string(std::istreambuf_iterator<char>(stream),
            std::istreambuf_iterator<char>());
    }
}
