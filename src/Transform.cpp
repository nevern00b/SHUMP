#include "Transform.h"



Transform::Transform(Entity* entity) : Component(entity),
    m_scale(1, 1, 1)
{

}

Transform::Transform() : Component(),
    m_scale(1, 1, 1)
{

}

Transform::Transform(const glm::vec3& translation, const glm::vec3& scale, const glm::quat& rotation) : Component(),
    m_translation(translation),
    m_scale(scale),
    m_rotation(rotation)
{

}

Transform::Transform(const glm::vec3& translation) : Component(),
    m_translation(translation),
    m_scale(1, 1, 1)
{

}


Transform::~Transform()
{

}

void Transform::update()
{
    m_matrix = glm::mat4_cast(m_rotation);
    m_matrix[3] = glm::vec4(m_translation, 1.0f);
    m_matrix[0][0] *= m_scale.x;
    m_matrix[1][1] *= m_scale.y;
    m_matrix[2][2] *= m_scale.z;
}

void Transform::setRotation(const glm::quat& quat)
{
    m_rotation = quat;
}

void Transform::setRotation(const glm::mat3& mat)
{
    setRotation(glm::quat_cast(mat));
}

void Transform::setRotation(float angle, const glm::vec3& axis)
{
    setRotation(glm::angleAxis(glm::radians(angle), axis));
}

void Transform::setRotation(float angle)
{
    setRotation(angle, glm::vec3(0, 0, 1));
}

void Transform::rotate(const glm::quat& quat)
{
    setRotation(quat * m_rotation);
}
void Transform::rotate(float angle, const glm::vec3& axis)
{
    rotate(glm::angleAxis(glm::radians(angle), axis));
}

void Transform::rotate(float angle)
{
    rotate(angle, glm::vec3(0, 0, 1));
}

void Transform::setTranslation(const glm::vec3& translation)
{
    m_translation = translation;
}

void Transform::setTranslation(float x, float y)
{
    setTranslation(glm::vec3(x, y, m_translation.z));
}

void Transform::translate(const glm::vec3& translation)
{
    setTranslation(m_translation + translation);
}

void Transform::translate(float x, float y)
{
    translate(glm::vec3(x, y, 0));
}

void Transform::setScale(const glm::vec3& scale)
{
    m_scale = scale;
}

void Transform::setScale(float scale)
{
	setScale(glm::vec3(scale));
}

void Transform::scale(const glm::vec3& scaleAmount)
{
	setScale(m_scale * scaleAmount);
}

void Transform::scale(float scaleAmount)
{
	scale(glm::vec3(scaleAmount));
}

glm::vec3 Transform::getRightVector()
{
    glm::mat3 rotation = glm::mat3_cast(m_rotation);
    return rotation[0];
}

glm::vec3 Transform::getUpVector()
{
    glm::mat3 rotation = glm::mat3_cast(m_rotation);
    return rotation[1];
}

glm::vec3 Transform::getForwardVector()
{
    glm::mat3 rotation = glm::mat3_cast(m_rotation);
    return rotation[2];
}

void Transform::applyTransform(const Transform& transform)
{
    translate(transform.m_translation);
    scale(transform.m_scale);
    rotate(transform.m_rotation);
}