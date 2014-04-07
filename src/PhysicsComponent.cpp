#include "PhysicsComponent.h"

//#include <btBulletCollisionCommon.h>
//#include <btBulletDynamicsCommon.h>
//#include <BulletCollision/CollisionShapes/btMaterial.h>
//#include "Utils.h"
//#include "Globals.h"
//#include "PhysicsManager.h"
//#include "Mesh.h"
//
//
//PhysicsComponent::PhysicsComponent(Entity* entity, PhysicsData* physicsData, const Transform& transform) : Transform(transform),
//    m_collisionShape(physicsData->m_collisionShape)
//{
//    btVector3 localInertia(0, 0, 0);
//    float mass = physicsData->m_mass;
//    if (mass > 0.0f)
//    {
//        m_collisionShape->calculateLocalInertia(mass, localInertia);
//    }
//
//    glm::mat4 matrix = transform.getMatrix();
//    btTransform initTransform = Utils::convertGLMTransformToBullet(matrix);
//    btDefaultMotionState* motionState = new btDefaultMotionState(initTransform);
//
//    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, m_collisionShape, localInertia);
//    m_rigidBody = new btRigidBody(rbInfo);
//    m_rigidBody->setUserPointer(entity);
//
//    if (physicsData->m_physicsMaterialOverride) // Multimaterial tri-mesh need to do this 
//    {
//        m_rigidBody->setCollisionFlags(m_rigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
//    } 
//    else
//    {
//        m_rigidBody->setFriction(physicsData->m_friction);
//        m_rigidBody->setRestitution(physicsData->m_restitution);
//    }
//
//
//
//    Globals::m_physicsManager->m_world->addRigidBody(m_rigidBody);
//}
//
//PhysicsComponent::~PhysicsComponent()
//{
//    btDiscreteDynamicsWorld* world = Globals::m_physicsManager->m_world;
//
//    // Delete constraints
//    while (m_rigidBody->getNumConstraintRefs())
//    {
//        btTypedConstraint* constraint = m_rigidBody->getConstraintRef(0);
//        Globals::m_physicsManager->m_world->removeConstraint(constraint);
//        delete constraint;
//    }
//
//    world->removeRigidBody(m_rigidBody);
//    delete m_rigidBody->getMotionState();
//    delete m_rigidBody;
//    // Collision shape is destroyed in PhysicsData
//}
//
//void PhysicsComponent::setRotation(const glm::quat& quat)
//{
//    btTransform worldTransform = m_rigidBody->getWorldTransform();
//    worldTransform.setRotation(Utils::convertGLMQuaternionToBullet(quat));
//    m_rigidBody->setWorldTransform(worldTransform);
//}
//
//void PhysicsComponent::setTranslation(const glm::vec3& translation)
//{
//    btTransform worldTransform = m_rigidBody->getWorldTransform();
//    worldTransform.setOrigin(Utils::convertGLMVectorToBullet(translation));
//    m_rigidBody->setWorldTransform(worldTransform);
//}
//
//void PhysicsComponent::setScale(const glm::vec3& scale)
//{
//    // TO-DO: copy the collision shape when this happens because we don't want other objects to be scaled
//    m_rigidBody->getCollisionShape()->setLocalScaling(Utils::convertGLMVectorToBullet(scale));
//}
//
//glm::mat4 PhysicsComponent::getMatrix() const
//{
//    return Utils::convertBulletTransformToGLM(m_rigidBody->getWorldTransform());
//}
//
//PhysicsMesh::PhysicsMesh(btTriangleIndexVertexArray* triangleMeshData, float* vertices, ushort* indices, uchar* triangleMaterials, btMaterial* materials) :
//    m_triangleMeshData(triangleMeshData),
//    m_vertices(vertices),
//    m_indices(indices),
//    m_triangleMaterials(triangleMaterials),
//    m_materials(materials)
//{
//
//}
//
//PhysicsMesh::~PhysicsMesh()
//{
//    delete m_triangleMeshData;
//    delete[] m_vertices;
//    delete[] m_indices;
//    delete[] m_triangleMaterials;
//    delete[] m_materials;
//}
//
//PhysicsData::PhysicsData() :
//    m_physicsMaterialOverride(false),
//    m_physicsMesh(0)
//{
//
//}
//
//PhysicsData::PhysicsData(float mass, float friction, float restitution, btCollisionShape* collisionShape) :
//    m_collisionShape(collisionShape),
//    m_mass(mass),
//    m_friction(friction),
//    m_restitution(restitution),
//    m_physicsMaterialOverride(false),
//    m_physicsMesh(0)
//{
//
//}
//
//PhysicsData::~PhysicsData()
//{
//    // Delete any collision shapes that make up the compound shape
//    if (m_collisionShape->isCompound())
//    {
//        btCompoundShape* m_compoundShape = (btCompoundShape*)m_collisionShape;
//        for (int i = 0; i < m_compoundShape->getNumChildShapes(); i++)
//        {
//            delete m_compoundShape->getChildShape(i);
//        }
//    }
//
//    // Delete the collision shape (either compound shape or not)
//    delete m_collisionShape;
//    delete m_physicsMesh;
//}