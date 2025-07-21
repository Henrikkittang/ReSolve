#pragma once

#include<string>
#include<unordered_map>

#include<glad/glad.h>
#include<glm/glm.hpp>

#include"core/asset.hpp"

struct ShaderProgramSource
{
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader : public Asset
{

public:

    Shader();
    Shader(const std::string& shaderProgram);
    ~Shader();
    Shader(Shader&& other);
    Shader& operator=(Shader&& other);

    bool load(const std::string& filepath)   override;
    bool unload() override;

    void bind() const;
    void unbind() const;

    void setUniform1f(const std::string& name, float value);
    void setUniform1i(const std::string& name, int value);

    void setUniform2f(const std::string& name, float v0,  float v1);

    void setUniform4f(const std::string& name, float v0,  float v1, float v2, float v3);

    void setUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:

    ShaderProgramSource parseShader(const std::string& string);
    uint32_t compileShader(uint32_t type, const std::string& source);
    uint32_t createShader(const std::string& vertexShader, const std::string& fragmentShader);
    
    uint32_t getUniformLocation(const std::string& name);

private:
    GLuint      m_renderID;
    std::unordered_map<std::string, int> m_uniformLocationCache;
};
