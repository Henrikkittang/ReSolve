#pragma once

#include<string>
#include<cstdint>

#include<glad/glad.h>
#include<glm/glm.hpp>

#include"core/asset.hpp"

class Texture : public Asset
{
public:
    
    Texture();
    Texture(int width, int height);
    ~Texture();
    Texture(Texture&& other);
    Texture& operator=(Texture&& other);

    Texture(const Texture& other) = delete;
    Texture operator=(const Texture& other) = delete;

    bool load(const std::string& filepath) override;
    bool unload() override;

    void bind(uint32_t slot = 0) const;
    void unbind() const;
    void update();

    glm::u8vec4 getPixel(int x, int y) const;
    void        setPixel(int x, int y, glm::u8vec4);

    inline int getWidth() { return m_width; }    
    inline int getHeight() { return m_height; }
private:
    GLuint      m_rendererID;
    uint8_t*    m_localBuffer;
    int         m_width, m_height, m_BBP;
}; 

