#include"util/util.hpp"

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


