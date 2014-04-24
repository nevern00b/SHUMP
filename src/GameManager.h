#pragma once

#include <vector>
#include <string>
#include <list>
#include "Common.h"

class Entity;
class DirLight;
class PointLight;
class Camera;

class GameManager
{

public:

    GameManager();
    ~GameManager();
    virtual void init();

    virtual void update();

    Entity* getEntity(const std::string& name);
    void addEntity(Entity* entity);
    void addDirLight(DirLight* dirLight);
    void addPointLight(PointLight* pointLight);
    void setCamera(Camera* camera);
    void removeDirLight(DirLight* dirLight);
    void removePointLight(PointLight* pointLight);

    Entity* m_rootEntity;
    Camera* m_camera;
    std::list<DirLight*> m_dirLights;
    std::list<PointLight*> m_pointLights;

private:

    std::list<Entity*> m_entities;
};