#pragma once

#include<GL/glew.h>

#include<string>
#include<cstdint>


class Texture
{
public:
    Texture(const std::string& filepath);
    ~Texture();

    void bind(uint32_t slot = 0) const;
    void unbind() const;

    inline int getWidth() { return m_width; }    
    inline int getHeight() { return m_height; }
private:
    GLuint      m_rendererID;
    std::string m_filepath;
    uint8_t*    m_localBuffer;
    int         m_width, m_height, m_BBP;
}; 

