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
    if( m_window == nullptr )
        glfwSetWindowSize(m_window, width, height);
}


void RenderWindow::setVSync(bool enabled)
{
    glfwSwapInterval(enabled ? 1 : 0);
}


// ! Untested
void RenderWindow::toggleFullscreen()
{
    static bool fullscreen = false;
    static int windowedX, windowedY, windowedWidth, windowedHeight;

    fullscreen = !fullscreen;

    if (fullscreen) {
        glfwGetWindowPos(m_window, &windowedX, &windowedY);
        glfwGetWindowSize(m_window, &windowedWidth, &windowedHeight);

        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    } else {
        glfwSetWindowMonitor(m_window, nullptr, windowedX, windowedY, windowedWidth, windowedHeight, 0);
    }
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


bool RenderWindow::isFullscreen() const
{
    return glfwGetWindowMonitor(m_window) != nullptr;
}
