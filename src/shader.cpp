#include"shader.hpp"

#include"renderer.hpp"

#include <GL/glew.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>    

// Constructors
Shader::Shader(const std::string& filepath)
    :m_filepath(filepath), m_rendererID(0)
{
    ShaderProgramSource source = parseShader(filepath);
    m_rendererID = createShader(source.vertexSource, source.fragmentSource); 
    // GLCall(glUseProgram(m_rendererID));
}

Shader::~Shader()
{
    GLCall( glDeleteProgram(m_rendererID) );
}

// Private function



ShaderProgramSource Shader::parseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    if( !stream.good() )
        std::cout << "Warning: The file at '" << filepath << "' was not found \n";

    enum class ShaderType
    {
        NONE=-1, VERTEX=0, FRAGMENT=1
    };

    std::string line; 
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }

    if( ss[0].str().length() == 0 )
        std::cout << "Warning: Vertex shader length is zero\n";
    if( ss[1].str().length() == 0 )
        std::cout << "Warning: Fragment shader length is zero\n";


    return { ss[0].str(), ss[1].str() };

}

uint32_t Shader::compileShader(uint32_t type, const std::string& source)
{
    uint32_t id = glCreateShader(type);
    const char* src = source.c_str();
    GLCall( glShaderSource(id, 1, &src, nullptr) );
    GLCall( glCompileShader(id) );

    int result;
    GLCall( glGetShaderiv(id, GL_COMPILE_STATUS, &result) );
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile shader " << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0; 
    }

    return id;
}

uint32_t Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    uint32_t program = glCreateProgram(); 
    uint32_t vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    uint32_t fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall( glAttachShader(program, vs) );
    GLCall( glAttachShader(program, fs) );

    GLCall( glLinkProgram(program) );
    GLCall( glValidateProgram(program) );

    GLCall( glDeleteShader(vs) );
    GLCall( glDeleteShader(fs) );

    return program;
}
 
uint32_t Shader::getUniformLocation(const std::string& name)
{
    if(m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(m_rendererID, name.c_str()));
    if(location == -1)
        std::cout << "Warning: uniform '" << name << "' dosent exists! \n";
    m_uniformLocationCache[name] = location;
    return location;
}

// Public functions
void Shader::bind() const
{
    GLCall( glUseProgram(m_rendererID) );
}

void Shader::unbind() const
{
    GLCall( glUseProgram(0) );
}


void Shader::setUniform1f(const std::string& name, float value)
{
    GLCall(glUniform1f(getUniformLocation(name), value));
}

void Shader::setUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(getUniformLocation(name), value));
}

void Shader::setUniform4f(const std::string& name, float v0,  float v1, float v2, float v3)
{
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}


void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCall( glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]) );
}
