#include"renderWindow.hpp"
#include"util.hpp"
#include"renderable.hpp"

#include<iostream>


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

/*
void RenderWindow::draw(float* vertexData, size_t size, const Shader& shader) const
{
    size_t vertex_count = size / 2; // 2 coordinates per vertex
    size_t quad_count = vertex_count / 4; // 4 vertices per quad
    size_t count = quad_count * 6; // 6 indices per quad

    uint32_t* indices = new uint32_t[count];
    for(size_t i = 0, vertex_index = 0; i < count; i += 6, vertex_index += 4)
    {
        indices[i + 0] = vertex_index + 0;
        indices[i + 1] = vertex_index + 1;
        indices[i + 2] = vertex_index + 2;
        indices[i + 3] = vertex_index + 2;
        indices[i + 4] = vertex_index + 3;
        indices[i + 5] = vertex_index + 0;
    }
    IndexBuffer ib = { indices, static_cast<uint32_t>(count) };
    delete[] indices;

    VertexBuffer vb = {vertexData, static_cast<uint32_t>(size * sizeof(float))};
    VertexBufferLayout layout; 
    layout.push<float>(2);
    
    VertexArray va;
    va.addBuffer(vb, layout);


    shader.bind();
    va.bind();
    ib.bind();
    
    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));

    shader.unbind();
    va.unbind();
    ib.unbind();
}*/

void RenderWindow::draw(float* vertexData, size_t size, const Shader& shader) const
{
    Renderable r{vertexData, static_cast<uint32_t>(size * sizeof(float)), 2};
    // r.update(vertexData, static_cast<uint32_t>(size * sizeof(float)));

    r.bind();
    GLCall( glDrawArrays(GL_QUADS, 0, size) );

    return;

    VertexBuffer vb = {vertexData, static_cast<uint32_t>(size * sizeof(float))};
    
    VertexBufferLayout layout; 
    layout.push<float>(2);
    
    VertexArray va;
    va.addBuffer(vb, layout);

    shader.bind();
    va.bind();
    
    GLCall( glDrawArrays(GL_QUADS, 0, size) );

    shader.unbind();
    va.unbind();
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