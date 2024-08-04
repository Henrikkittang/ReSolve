#include"texture.hpp"

#include<stb_image/stb_image.h>

#include"util.hpp"

Texture::Texture(const std::string& filepath)
    :m_rendererID(0), m_filepath(filepath), m_localBuffer(nullptr), m_width(0), m_height(0), m_BBP(0)
{
    stbi_set_flip_vertically_on_load(true);
    m_localBuffer = stbi_load(filepath.c_str(), &m_width, &m_height, &m_BBP, 4);

    GLCall( glGenTextures(1, &m_rendererID) );
    GLCall( glBindTexture(GL_TEXTURE_2D, m_rendererID) );

    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) );
    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );
    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE) );
    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE) );
 
    GLCall( glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer) );
    
    unbind();

    if( m_localBuffer )
        stbi_image_free(m_localBuffer);
    m_localBuffer = nullptr;
}

Texture::~Texture()
{
    GLCall( glDeleteTextures(1, &m_rendererID) );
}

Texture::Texture(Texture&& other)
    :m_rendererID(other.m_rendererID), m_filepath(other.m_filepath), m_localBuffer(other.m_localBuffer), m_width(other.m_width), m_height(other.m_height), m_BBP(other.m_BBP)
{
    other.m_rendererID  = 0;
    other.m_localBuffer = nullptr;
}

Texture& Texture::operator=(Texture&& other)
{
    if(this != &other)
    {
        GLCall( glDeleteTextures(1, &m_rendererID) );

        m_rendererID  = other.m_rendererID;
        m_filepath    = std::move( other.m_filepath );
        m_localBuffer = other.m_localBuffer;
        m_width       = other.m_width;
        m_height      = other.m_height;
        m_BBP         = other.m_BBP;

        other.m_rendererID  = 0;
        other.m_localBuffer = nullptr;        

    }
    return *this;
}

void Texture::bind(uint32_t slot) const
{
    GLCall( glActiveTexture(GL_TEXTURE0 + slot) );
    GLCall( glBindTexture(GL_TEXTURE_2D, m_rendererID) );
}

void Texture::unbind() const
{
    GLCall( glBindTexture(GL_TEXTURE_2D, 0) );
}