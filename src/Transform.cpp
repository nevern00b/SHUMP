#include "Transform.h"

Transform::Transform() :
    m_scale(1, 1, 1)
{

}

Transform::Transform(const glm::vec3& translation, const glm::vec3& scale, const glm::quat& rotation) :
    m_translation(translation),
    m_scale(scale),
    m_rotation(rotation)
{
    finalize();
}

Transform::Transform(const glm::vec3& translation) :
    m_translation(translation),
    m_scale(1, 1, 1)
{
    finalize();
}


Transform::~Transform()
{

}

void Transform::setRotation(const glm::quat& quat)
{
    m_rotation = quat;
    finalize();
}

void Transform::setRotation(const glm::mat3& mat)
{
    setRotation(glm::quat_cast(mat));
}
void Transform::setRotation(float angle, const glm::vec3& axis)
{
    setRotation(glm::angleAxis(glm::radians(angle), axis));
}
void Transform::applyRotation(const glm::quat& quat)
{
    setRotation(quat * m_rotation);
}
void Transform::applyRotation(float angle, const glm::vec3& axis)
{
    applyRotation(glm::angleAxis(glm::radians(angle), axis));
}

void Transform::setTranslation(const glm::vec3& translation)
{
    m_translation = translation;
    finalize();
}
void Transform::applyTranslation(const glm::vec3& translation)
{
    setTranslation(m_translation + translation);
}

void Transform::setScale(const glm::vec3& scale)
{
    m_scale = scale;
    finalize();
}

void Transform::applyScale(const glm::vec3& scale)
{
    setScale(m_scale * scale);
}

glm::mat4 Transform::getMatrix() const
{
    return m_matrix;
}

glm::vec3 Transform::getRightVector()
{
    // TO-DO: Scale
    return glm::vec3(m_matrix[0]);
}

glm::vec3 Transform::getUpVector()
{
    // TO-DO: Scale
    return glm::vec3(m_matrix[1]);
}

glm::vec3 Transform::getForwardVector()
{
    // TO-DO: Scale
    return glm::vec3(m_matrix[2]);
}

void Transform::finalize()
{
    m_matrix = glm::mat4_cast(m_rotation);
    m_matrix[3] = glm::vec4(m_translation, 1.0f);
    m_matrix[0][0] *= m_scale.x;
    m_matrix[1][1] *= m_scale.y;
    m_matrix[2][2] *= m_scale.z;
}

void Transform::applyTransform(const Transform& transform)
{
    applyTranslation(transform.m_translation);
    applyScale(transform.m_scale);
    applyRotation(transform.m_rotation);
}