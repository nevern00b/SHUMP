#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
public:

    Transform();
    Transform(const glm::vec3& translation, const glm::vec3& scale, const glm::quat& rotation);
    Transform(const glm::vec3& translation);
    ~Transform();

    virtual void setRotation(const glm::quat& quat);
    void setRotation(const glm::mat3& mat);
    void setRotation(float angle, const glm::vec3& axis);
    void applyRotation(const glm::quat& quat);
    void applyRotation(float angle, const glm::vec3& axis);
    
    virtual void setTranslation(const glm::vec3& translation);
    void applyTranslation(const glm::vec3& translation);

    virtual void setScale(const glm::vec3& scale);
    void applyScale(const glm::vec3& scale);
    
    void applyTransform(const Transform& transform);


    virtual glm::mat4 getMatrix() const;
    glm::vec3 getRightVector();
    glm::vec3 getUpVector();
    glm::vec3 getForwardVector();

    glm::quat m_rotation;
    glm::vec3 m_translation;
    glm::vec3 m_scale;

private:

    glm::mat4 m_matrix;

    void finalize();

};