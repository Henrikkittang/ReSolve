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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    auto camera = Camera{(float)getSize().x, (float)getSize().y};
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
        
        m_window       = other.m_window;
        m_basicShader  = std::move( other.m_basicShader );
        
        other.m_window = nullptr;
    }
    return *this;
}


void RenderWindow::clear() const
{
    // glClear(GL_COLOR_BUFFER_BIT);  
    GLCall( glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ); 
}


void RenderWindow::draw(const Renderable& renderable, Ref<Shader> shader) const
{
    shader->bind();
    renderable.bind();

    GLCall(glDrawElements(GL_TRIANGLES, renderable.indexSize(), GL_UNSIGNED_INT, nullptr));

    shader->unbind();
    renderable.unbind();
}

void RenderWindow::draw(const Renderable& renderable) const
{
    renderable.bind();
    m_basicShader.bind();

    GLCall(glDrawElements(GL_TRIANGLES, renderable.indexSize(), GL_UNSIGNED_INT, nullptr));

    renderable.unbind();
    m_basicShader.unbind();
}

void RenderWindow::update()
{
    glfwSwapBuffers(m_window);
    glfwPollEvents();      
}

// --------- Toggles ------------------------
// ? Maybe have these function issue events to the application



// ! Add a framebuffer_size_callback
void RenderWindow::resize(int width, int height)
{
    if( m_window != nullptr )
        glfwSetWindowSize(m_window, width, height);
}


void RenderWindow::setVSync(bool enabled)
{
    glfwSwapInterval(enabled ? 1 : 0);
}



// --------- Getters ------------------------


glm::ivec2 RenderWindow::getMousePosition() const
{
    double xpos, ypos;
    glfwGetCursorPos(m_window, &xpos, &ypos);
    return {xpos, ypos};
}


glm::ivec2 RenderWindow::getSize() const
{
    glm::ivec2 size;
    glfwGetWindowSize(m_window, &size.x, &size.y);
    return size;
}

GLFWwindow* RenderWindow::getNativeHandle() 
{ 
    return m_window; 
}	


bool RenderWindow::isKeyPressed(int key) const
{
    return glfwGetKey(m_window, key) == GLFW_PRESS;
}

bool RenderWindow::windowShouldClose() const
{
    return glfwWindowShouldClose( m_window );
}






void RenderWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Update the OpenGL viewport to the new framebuffer size
    glViewport(0, 0, width, height);

   
}
