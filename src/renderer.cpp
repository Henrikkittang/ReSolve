#include "renderer.hpp"
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


void Renderer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);   
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.bind();
    va.bind();
    ib.bind();

    
    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));

}
