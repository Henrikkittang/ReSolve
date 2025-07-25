#include"graphics/renderWindow.hpp"


#include"core/camera.hpp"
#include"graphics/shader.hpp"
#include"graphics/renderable.hpp"
#include"util/log.hpp"

RenderWindow::RenderWindow()
    : m_window(nullptr), m_basicShader()
{}


RenderWindow::RenderWindow(GLFWwindow* window)
    : m_window(window), m_basicShader(s_basicShaderSource)
{
    // auto camera = Camera{(float)getSize().x, (float)getSize().y};
    auto camera = Camera{960.0, 540.0};
    auto mvp = camera.getMVP();

    m_basicShader.bind();
    m_basicShader.setUniformMat4f("uMVP", mvp);
    m_basicShader.unbind();
}

RenderWindow::~RenderWindow()
{
    if( m_window != nullptr )
        glfwDestroyWindow(m_window);    
}

RenderWindow::RenderWindow(RenderWindow&& other)
    : m_window(other.m_window), m_basicShader( std::move(other.m_basicShader) )
{
    other.m_window = nullptr; 
}

RenderWindow& RenderWindow::operator=(RenderWindow&& other)
{
    if (this != &other) {
        if (m_window) 
            glfwDestroyWindow(m_window);
        
        m_window = other.m_window;
        m_basicShader = std::move( other.m_basicShader );
        other.m_window = nullptr;
    }
    return *this;
}


void RenderWindow::clear() const
{
    // glClear(GL_COLOR_BUFFER_BIT);  
    GLCall( glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ); 
}



void RenderWindow::draw(const Renderable& renderable) const
{
    renderable.bind();
    m_basicShader.bind();

    // GLCall( glDrawArrays(GL_TRIANGLES, 0, renderable.vertexCount()) );
    GLCall(glDrawElements(GL_TRIANGLES, renderable.indexCount(), GL_UNSIGNED_INT, nullptr));

    renderable.unbind();
    m_basicShader.unbind();
}

void RenderWindow::draw(const glm::vec2* vertecies, uint32_t size, PrimitiveType type) const
{
    
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