#include<iostream>

#include"graphics/renderWindow.hpp"
#include"graphics/renderable.hpp"
#include"util/util.hpp"


RenderWindow::RenderWindow()
    : m_window(nullptr)
{}


RenderWindow::RenderWindow(GLFWwindow* window)
    : m_window(window)
{}

RenderWindow::~RenderWindow()
{
    // if( m_window != nullptr )
    //     glfwDestroyWindow(m_window);    
}

RenderWindow::RenderWindow(RenderWindow&& other)
    : m_window(other.m_window)
{
    other.m_window = nullptr; 
}

RenderWindow& RenderWindow::operator=(RenderWindow&& other)
{
    if (this != &other) {
        if (m_window) 
            glfwDestroyWindow(m_window);
        
        m_window = other.m_window;
        other.m_window = nullptr;
    }
    return *this;
}


void RenderWindow::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);  
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
}

void RenderWindow::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.bind();
    va.bind();
    ib.bind();
    
    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));

    shader.unbind();
    va.unbind();
    ib.unbind();
}


void RenderWindow::draw(const Renderable& renderable, const Shader& shader) const
{
    renderable.bind();
    shader.bind();
    GLCall( glDrawArrays(GL_QUADS, 0, renderable.size()) );
    renderable.unbind();
    shader.unbind();
}

bool RenderWindow::windowShouldClose() const
{
    return glfwWindowShouldClose( m_window );
}

void RenderWindow::update()
{
    glfwSwapBuffers(m_window);
    glfwPollEvents();      
}

glm::ivec2 RenderWindow::getSize() const
{
    glm::ivec2 size;
    glfwGetWindowSize(m_window, &size.x, &size.y);
    return size;
}

bool RenderWindow::isKeyPressed(int key) const
{
    return glfwGetKey(m_window, key) == GLFW_PRESS;
}