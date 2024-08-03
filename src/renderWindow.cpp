#include"renderWindow.hpp"
#include<iostream>

void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while(GLenum error = glGetError() )
    {
        std::cout <<  "[OpenGl error] (" << error << "): " << function << " " << file << ":" << line << " \n";
        return false;
    }
    return true;
}


RenderWindow::RenderWindow(uint32_t width, uint32_t height)
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize glfw \n";
    }

    m_window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!m_window)
    {
        std::cerr << "Failed to create glfw window \n";
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_window);
    if(glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initilize glew \n";
    }    

    GLCall( glEnable(GL_BLEND) );
    GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );
}

RenderWindow::~RenderWindow()
{
    glfwTerminate();
}


void RenderWindow::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);   
}

void RenderWindow::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.bind();
    va.bind();
    ib.bind();

    
    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
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