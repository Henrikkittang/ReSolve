#include"graphics/shader.hpp"


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>    


#include<glad/glad.h>

#include"util/util.hpp"
#include"util/timer.hpp"

Shader::Shader()
    :m_renderID(0)
{}


Shader::Shader(const std::string& shaderProgram)
    :m_renderID(0)
{
    ShaderProgramSource source = parseShader(shaderProgram);
    m_renderID = createShader(source.vertexSource, source.fragmentSource); 

    DEBUG_CHECK(m_renderID == 0, "Creating shader failed");
}


Shader::~Shader()
{
    if(m_renderID != 0)
        GLCall( glDeleteProgram(m_renderID) );
    m_uniformLocationCache.clear();
    m_renderID = 0;
}


Shader::Shader(Shader&& other)  
    : m_renderID(other.m_renderID), m_uniformLocationCache(other.m_uniformLocationCache) 
{
    other.m_renderID = 0; 
}

Shader& Shader::operator=(Shader&& other) 
{
    if (this != &other) 
    {
        GLCall( glDeleteProgram(m_renderID) );
        
        m_renderID = other.m_renderID;
        m_uniformLocationCache = std::move( other.m_uniformLocationCache );
        
        other.m_renderID = 0;
    }
    return *this;
}

bool Shader::load(const std::string& filepath)
{
    std::ifstream file(filepath);
    
    std::stringstream buffer;
    buffer << file.rdbuf();

    ShaderProgramSource source = parseShader(buffer.str());
    m_renderID = createShader(source.vertexSource, source.fragmentSource); 

    if( m_renderID == 0 )
    {
        DEBUG_LOG("Creating shader failed");
        return false; 
    }
    return true;
}

bool Shader::unload()
{
    if(m_renderID != 0)
        GLCall( glDeleteProgram(m_renderID) );

    m_uniformLocationCache.clear();
    m_renderID = 0;

    return true;
}


void Shader::bind() const
{
    GLCall( glUseProgram(m_renderID) );
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

void Shader::setUniform2f(const std::string& name, float v0,  float v1)
{
    GLCall(glUniform2f(getUniformLocation(name), v0, v1));
}

void Shader::setUniform4f(const std::string& name, float v0,  float v1, float v2, float v3)
{
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}


void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCall( glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]) );
}


ShaderProgramSource Shader::parseShader(const std::string& source)
{
    std::istringstream stream(source);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else if (type != ShaderType::NONE)
        {
            ss[(int)type] << line << '\n';
        }
    }

    DEBUG_CHECK(ss[0].str().empty(), "Warning: Vertex shader length is zero\n");
    DEBUG_CHECK(ss[1].str().empty(), "Warning: Fragment shader length is zero\n");

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
        GLCall( glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length) );
        char* message = (char*)alloca(length * sizeof(char));
        GLCall( glGetShaderInfoLog(id, length, &length, message) );
        std::cout << "Failed to compile shader " << std::endl;
        std::cout << message << std::endl;
        GLCall( glDeleteShader(id) );
        return 0; 
    }

    return id;
}

uint32_t Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    uint32_t program = glCreateProgram() ;
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

    GLCall(int location = glGetUniformLocation(m_renderID, name.c_str()));
    if(location == -1)
        std::cout << "Warning: uniform '" << name << "' dosent exists! \n";
    m_uniformLocationCache[name] = location;
    return location;
}