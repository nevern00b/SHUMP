//#pragma once
//
//#include <vector>
//#include <glm/glm.hpp>
//#include "Utils.h"
//
//class b2World;
//class PhysicsComponent;
//
//class PhysicsManager
//{
//public:
//    PhysicsManager();
//    ~PhysicsManager();
//    void update();
//
//    b2World* m_world;
//
//private:    
//
//};
//
//namespace Utils
//{
//    glm::mat4 convertBulletTransformToGLM(const btTransform& transform);
//    btTransform convertGLMTransformToBullet(const glm::mat4& transform);
//    glm::quat convertBulletQuaternionToGLM(const btQuaternion& quaternion);
//    btQuaternion convertGLMQuaternionToBullet(const glm::quat& quaternion);
//    glm::vec3 convertBulletVectorToGLM(const btVector3& vector);
//    btVector3 convertGLMVectorToBullet(const glm::vec3& vector);
//
//    btBoxShape* createBoxShape(const glm::vec3& dimensions);
//    btBoxShape* createBoxShape(float width, float height, float depth);
//    btSphereShape* createSphereShape(float radius);
//    btCylinderShape* createCylinderShape(float height, float radiusWidth, float radiusDepth);
//    btCapsuleShape* createCapsuleShape(float radius, float height);
//    btConeShape* createConeShape(float radius, float height);
//    btConvexHullShape* createConvexHullShape(const std::vector<glm::vec3>& vertices);
//    btCompoundShape* createCompoundShape(const std::vector<btCollisionShape*>& shapes, const std::vector<glm::mat4>& transforms);
//    void getCollisionShapeAABB(btCollisionShape* collisionShape, glm::vec3& min, glm::vec3& max);
//}