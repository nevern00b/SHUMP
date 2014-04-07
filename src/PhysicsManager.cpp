#include "PhysicsManager.h"


//#include <Box2D/Dynamics/b2World.h>
//#include <Box2D/Common/b2Math.h>
//#include <glm/gtc/type_ptr.hpp>
//#include "Globals.h"
//#include "UIManager.h"
//#include "Common.h"
//#include "Entity.h"
//#include "PhysicsComponent.h"
//
//PhysicsManager::PhysicsManager()
//{
//   // Create world
//    m_world = new b2World(b2Vec2(0.0f, 10.0f));
//    b2ContactListener* contactListener = new ContactListener();
//    world.setContactListener(contactListener);
//}
//
//PhysicsManager::~PhysicsManager()
//{
//    delete m_world;
//}
//
//void PhysicsManager::update()
//{
//    float frameTime = Globals::m_uiManager->m_frameTime;
//    float desiredFrameTime = Globals::m_uiManager->m_desiredFrameTime;
//    uint maxSubsteps = 100; // some arbitrary large number
//
//    m_world->stepSimulation(frameTime, maxSubsteps, desiredFrameTime);
//}
//
//void PhysicsManager::addConstraint(PhysicsComponent* source, PhysicsComponent* target, ConstraintData* data)
//{
//    // Get the constraint position in the target's frame of reference
//    glm::vec3 targetPos = data->m_position;
//    if (target)
//    {
//        glm::mat4 sourceTransform = source->getMatrix();
//        glm::mat4 targetTransform = target->getMatrix();
//        targetPos = glm::vec3(glm::inverse(targetTransform) * sourceTransform * glm::vec4(targetPos, 1.0));
//    }
//
//    btVector3 constraintPosSource = Utils::convertGLMVectorToBullet(data->m_position);
//    btVector3 constraintPosTarget = Utils::convertGLMVectorToBullet(targetPos);
//
//    if (data->m_type == ConstraintType::HINGE)
//    {
//        btVector3 constraintAxis = Utils::convertGLMVectorToBullet(data->m_axis);
//
//        if (target)
//        {
//            btHingeConstraint* hinge = new btHingeConstraint(*source->m_rigidBody, *target->m_rigidBody, constraintPosSource, constraintPosTarget, constraintAxis, constraintAxis);
//            hinge->setLimit(data->m_angleMin, data->m_angleMax);
//            m_world->addConstraint(hinge);
//        }
//        else
//        {
//            btHingeConstraint* hinge = new btHingeConstraint(*source->m_rigidBody, constraintPosSource, constraintAxis);
//            hinge->setLimit(data->m_angleMin, data->m_angleMax);
//            m_world->addConstraint(hinge);
//        }
//    }
//    else if (data->m_type == ConstraintType::POINT2POINT)
//    {
//        if (target)
//        {
//            btPoint2PointConstraint* ball = new btPoint2PointConstraint(*source->m_rigidBody, *target->m_rigidBody, constraintPosSource, constraintPosTarget);
//            m_world->addConstraint(ball);
//        }
//        else
//        {
//            btPoint2PointConstraint* ball = new btPoint2PointConstraint(*source->m_rigidBody, constraintPosSource);
//            m_world->addConstraint(ball);
//        }
//    }
//}
//
//namespace Utils
//{
//    glm::mat4 convertBulletTransformToGLM(const btTransform& transform)
//    {
//        float data[16];
//        transform.getOpenGLMatrix(data);
//        return glm::make_mat4(data);
//    }
//    btTransform convertGLMTransformToBullet(const glm::mat4& transform)
//    {
//        btTransform bulletTransform;
//        bulletTransform.setFromOpenGLMatrix(glm::value_ptr(transform));
//        return bulletTransform;
//    }
//    glm::quat convertBulletQuaternionToGLM(const btQuaternion& quaternion)
//    {
//        return glm::quat(quaternion.getW(), quaternion.getX(), quaternion.getY(), quaternion.getZ());
//    }
//
//    btQuaternion convertGLMQuaternionToBullet(const glm::quat& quaternion)
//    {
//        return btQuaternion(quaternion.x, quaternion.y, quaternion.z, quaternion.w);
//    }
//
//    glm::vec3 convertBulletVectorToGLM(const btVector3& vector)
//    {
//        return glm::vec3(vector.getX(), vector.getY(), vector.getZ());
//    }
//
//    btVector3 convertGLMVectorToBullet(const glm::vec3& vector)
//    {
//        return btVector3(vector.x, vector.y, vector.z);
//    }
//
//    btBoxShape* createBoxShape(const glm::vec3& dimensions)
//    {
//        return createBoxShape(dimensions.x, dimensions.y, dimensions.z);
//    }
//    btBoxShape* createBoxShape(float width, float height, float depth)
//    {
//        return new btBoxShape(btVector3(width, height, depth));
//    }
//
//    btSphereShape* createSphereShape(float radius)
//    {
//        return new btSphereShape(radius);
//    }
//
//    btCylinderShape* createCylinderShape(float height, float radiusWidth, float radiusDepth)
//    {
//        return new btCylinderShape(btVector3(radiusWidth, height, radiusDepth));
//    }
//
//    btCapsuleShape* createCapsuleShape(float radius, float height)
//    {
//        return new btCapsuleShape(radius, height);
//    }
//
//    btConeShape* createConeShape(float radius, float height)
//    {
//        return new btConeShape(radius, height);
//    }
//
//    btConvexHullShape* createConvexHullShape(const std::vector<glm::vec3>& vertices)
//    {
//        return new btConvexHullShape(&vertices[0][0], vertices.size(), sizeof(glm::vec3));
//    }
//
//    btCompoundShape* createCompoundShape(const std::vector<btCollisionShape*>& shapes, const std::vector<glm::mat4>& localTransforms)
//    {
//        btCompoundShape* compoundShape = new btCompoundShape();
//        for (uint i = 0; i < shapes.size(); i++)
//        {
//            compoundShape->addChildShape(Utils::convertGLMTransformToBullet(localTransforms.at(i)), shapes.at(i));
//        }
//        return compoundShape;
//    }
//
//    void getCollisionShapeAABB(btCollisionShape* collisionShape, glm::vec3& min, glm::vec3& max)
//    {
//        btVector3 minAABBBullet, maxAABBBullet;
//        collisionShape->getAabb(btTransform::getIdentity(), minAABBBullet, maxAABBBullet);
//        min = Utils::convertBulletVectorToGLM(minAABBBullet);
//        max = Utils::convertBulletVectorToGLM(maxAABBBullet);
//    }
//
//}
//