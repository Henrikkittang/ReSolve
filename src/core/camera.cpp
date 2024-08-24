#include"camera.hpp"


Camera::Camera() 
    : 
    m_position(0, 0, 0), 
    m_model(glm::mat4(1.0f)), 
    m_view(glm::translate(glm::mat4(1.0f), m_position)),
    m_proj(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f)),
    m_mvp(m_proj * m_view * m_model)
{}


Camera::Camera(float width, float height) 
    : 
    m_position(0, 0, 0), 
    m_model(glm::mat4(1.0f)), 
    m_view(glm::translate(glm::mat4(1.0f), m_position)),
    m_proj(glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f)),
    m_mvp(m_proj * m_view * m_model)
{}

const glm::mat4& Camera::getMVP() const
{
    return m_mvp;
}

void Camera::setPosition(const glm::vec3& position)
{
    m_position = position;
    recalucateView();
}

const glm::vec3& Camera::getPosition() const
{
    return m_position;
}

void Camera::recalucateView()
{
    m_view = glm::translate(glm::mat4(1.0f), m_position);
}
