#pragma once

#include<string>
#include<unordered_map>

#include<glm/glm.hpp>

struct ShaderProgramSource
{
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader
{

public:

    Shader() = default;
    Shader(const std::string& filepath);
    ~Shader();

    void bind() const;
    void unbind() const;

    void setUniform1f(const std::string& name, float value);
    void setUniform1i(const std::string& name, int value);

    void setUniform2f(const std::string& name, float v0,  float v1);

    void setUniform4f(const std::string& name, float v0,  float v1, float v2, float v3);

    void setUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:

    ShaderProgramSource parseShader(const std::string& filepath);
    uint32_t compileShader(uint32_t type, const std::string& source);
    uint32_t createShader(const std::string& vertexShader, const std::string& fragmentShader);
    
    uint32_t getUniformLocation(const std::string& name);

private:
    std::string m_filepath;
    uint32_t    m_renderId;
    std::unordered_map<std::string, int> m_uniformLocationCache;
};
