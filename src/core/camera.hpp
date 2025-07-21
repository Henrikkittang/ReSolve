#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>


class Camera
{
public:

    Camera();
    Camera(float width, float height);
    const glm::mat4& getMVP() const;
    
    void setPosition(const glm::vec3& position);
    const glm::vec3& getPosition() const;

private:
    void recalucateView();

private:

    glm::vec3 m_position;

    glm::mat4 m_model;
    glm::mat4 m_view;
    glm::mat4 m_proj;
    glm::mat4 m_mvp;
};