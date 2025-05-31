#pragma once

#include <glad/glad.h>

#include<string>
#include<cstdint>
#include<glm/glm.hpp>

class Texture 
{
public:
    
    Texture();
    Texture(int width, int height);
    Texture(const std::string& filepath);
    ~Texture();
    Texture(Texture&& other);
    Texture& operator=(Texture&& other);

    Texture(const Texture& other) = delete;
    Texture operator=(const Texture& other) = delete;

    void bind(uint32_t slot = 0) const;
    void unbind() const;
    void update();

    glm::u8vec4 getPixel(int x, int y) const;
    void        setPixel(int x, int y, glm::u8vec4);

    inline int getWidth() { return m_width; }    
    inline int getHeight() { return m_height; }
private:
    GLuint      m_rendererID;
    std::string m_filepath;
    uint8_t*    m_localBuffer;
    int         m_width, m_height, m_BBP;
}; 

