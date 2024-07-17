#pragma once
#include<string>
#include<unordered_map>
#include <cstdint>

struct ShaderProgramSource
{
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader
{

public:
    Shader(const std::string& filepath);
    ~Shader();

    void bind() const;
    void unbind() const;

    void setUniform4f(const std::string& name, float f0,  float f1, float f2, float f3);
private:
    std::string m_filepath;
    uint32_t m_rendererID;
    std::unordered_map<std::string, int> m_uniformLocationCache;
private:

    ShaderProgramSource parseShader(const std::string& filepath);
    uint32_t compileShader(uint32_t type, const std::string& source);
    uint32_t createShader(const std::string& vertexShader, const std::string& fragmentShader);

    
    uint32_t getUniformLocation(const std::string& name);
};
