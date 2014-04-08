#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
public:
    // All rotations are in degrees

    Transform();
    Transform(const glm::vec3& translation, const glm::vec3& scale, const glm::quat& rotation);
    Transform(const glm::vec3& translation);
    ~Transform();
    
    virtual void update();

    virtual void setRotation(const glm::quat& quat);
    void setRotation(const glm::mat3& mat);
    void setRotation(float angle, const glm::vec3& axis);
    void setRotation(float angle); // About z-axis
    void rotate(const glm::quat& quat);
    void rotate(float angle, const glm::vec3& axis);
    void rotate(float angle); // About z-axis
 
    virtual void setTranslation(const glm::vec3& translation);
    void setTranslation(float x, float y);
    void setDepth(float z);
    void translate(const glm::vec3& translation);
    void translate(float x, float y);

    virtual void setScale(const glm::vec3& scale);
    void scale(const glm::vec3& scale);
    
    void applyTransform(const Transform& transform);

    glm::vec3 getRightVector();
    glm::vec3 getUpVector();
    glm::vec3 getForwardVector();

    glm::mat4 m_matrix;
    glm::quat m_rotation;
    glm::vec3 m_translation;
    glm::vec3 m_scale;

protected:

    

};