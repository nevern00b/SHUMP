#include "Player.h"

#include <Box2D/Box2D.h>
#include "Material.h"
#include "Utils.h"
#include "Globals.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "PhysicsManager.h"
#include "DataManager.h"
#include "UIManager.h"

Player::Player() : Entity(0)
{
    Material* greenMaterial = new Material();
    greenMaterial->m_diffuseColor = glm::vec4(0, 1, 0, 1);

    b2Shape* cubeShape = Utils::createBoxShape(1.0f, 1.0f);
    Mesh* cubeMesh = Globals::m_dataManager->getMesh("cube");

    PhysicsData* playerPhysicsData = new PhysicsData(cubeShape, 1.0f, 0.2f, 0.5f);
    PhysicsComponent* playerPhysics = new PhysicsComponent(this, playerPhysicsData);

    std::vector<Material*> playerMaterials = { greenMaterial };
    RenderComponent* playerRender = new RenderComponent(this, cubeMesh, playerMaterials);

    m_transform->setTranslation(0, 5);
}

Player::~Player()
{

}

void Player::update()
{
    Entity::update();

    float speed = 10.0f;
    b2Body* body = m_physics->m_body;

    b2Vec2 vel = body->GetLinearVelocity();
    b2Vec2 desiredVel(0, 0);

    // Get keyboard input
    if (Globals::m_uiManager->isKeyDown(GLFW_KEY_A))
        desiredVel.x -= speed;
    if (Globals::m_uiManager->isKeyDown(GLFW_KEY_D))
        desiredVel.x += speed;
    if (Globals::m_uiManager->isKeyDown(GLFW_KEY_W))
        desiredVel.y += speed;
    if (Globals::m_uiManager->isKeyDown(GLFW_KEY_S))
        desiredVel.y -= speed;

    if (Globals::m_uiManager->isKeyDown(GLFW_KEY_SPACE))
    {
        shoot();
    }


    b2Vec2 velChange = desiredVel - vel;
    b2Vec2 impulse = body->GetMass() * velChange;
    body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
}

void Player::shoot()
{

}