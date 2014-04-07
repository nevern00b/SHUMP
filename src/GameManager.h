#pragma once

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
    void init();

    void update();

    Entity* getEntity(const std::string& name);
    void addEntity(Entity* entity);
    void addDirLight(DirLight* dirLight);
    void addPointLight(PointLight* pointLight);
    void setCamera(Camera* camera);
    void removeEntity(Entity* entity);
    void removeDirLight(DirLight* dirLight);
    void removePointLight(PointLight* pointLight);
    void setSkybox(const std::string& filename);

    Entity* m_rootEntity;
    Camera* m_camera;
    std::list<DirLight*> m_dirLights;
    std::list<PointLight*> m_pointLights;

private:

    std::list<Entity*> m_entities;
    std::list<Camera*> m_cameras;
};