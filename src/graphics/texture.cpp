#include"graphics/texture.hpp"

#include<cstring>

#include<stb_image/stb_image.h>

#include"util/log.hpp"


Texture::Texture()
    :m_rendererID(0), m_localBuffer(nullptr), m_width(0), m_height(0), m_BBP(0)
{}

Texture::Texture(int width, int height)
    :m_rendererID(0), m_localBuffer(nullptr), m_width(width), m_height(height), m_BBP(32)
{
    // Using malloc for stb_image compatibility
    m_localBuffer = (uint8_t*)malloc(4*m_width*m_height);
    memset(m_localBuffer, 0, 4*m_width*m_height);

   
    GLCall( glGenTextures(1, &m_rendererID) );
    GLCall( glBindTexture(GL_TEXTURE_2D, m_rendererID) );

    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR) );
    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );
    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE) );
    GLCall( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE) );
 
    GLCall( glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer) );
    
    unbind();
}



Texture::~Texture()
{
    if( m_rendererID != 0 )
        GLCall( glDeleteTextures(1, &m_rendererID) );
 
    if( m_localBuffer )
        stbi_image_free(m_localBuffer);

    m_localBuffer = nullptr;
    m_rendererID  = 0;
}

Texture::Texture(Texture&& other)
    :m_rendererID(other.m_rendererID), m_localBuffer(other.m_localBuffer), m_width(other.m_width), m_height(other.m_height), m_BBP(other.m_BBP)
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
        m_localBuffer = other.m_localBuffer;
        m_width       = other.m_width;
        m_height      = other.m_height;
        m_BBP         = other.m_BBP;

        other.m_rendererID  = 0;
        other.m_localBuffer = nullptr;        

    }
    return *this;
}


bool Texture::load(const std::string& filepath) 
{
    CHECK_WARN(m_localBuffer != nullptr, "Overwriting local buffer in texture");


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

    if (!m_localBuffer) 
    {
        LOG_WARN("Failed to load texture: " + filepath);
        return false;
    }

    return true;    
}


bool Texture::unload() 
{
    if (m_rendererID != 0)
        GLCall(glDeleteTextures(1, &m_rendererID));

    if (m_localBuffer)
        stbi_image_free(m_localBuffer);

    m_localBuffer = nullptr;
    m_rendererID = 0;

    return true;  
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

void Texture::update()
{
    bind();

    glTexSubImage2D(GL_TEXTURE_2D,   // Target texture type
                0,                   // Mipmap level (0 = base level)
                0, 0,                // Offset (x, y) in the texture to start replacing
                m_width, m_height,   // Width and height of the data you're updating
                GL_RGBA,             // Format of the pixel data (e.g., GL_RGBA)
                GL_UNSIGNED_BYTE,    // Data type of the pixel data
                m_localBuffer);      // Pointer to the new data
    
    unbind();
}


glm::u8vec4 Texture::getPixel(int x, int y) const
{
// #if DEBUG
//     if( x >= m_width - 3 || x < 0 || y >= m_height - 3 || y < 0)
//         std::cout << "Position out of bound in texture \n";
//     if(!m_localBuffer)
//         std::cout << "Local buffer is nullptr \n";
// #endif

    return { 
        m_localBuffer[y*m_width*4 + x*4 + 0],  
        m_localBuffer[y*m_width*4 + x*4 + 1],  
        m_localBuffer[y*m_width*4 + x*4 + 2],  
        m_localBuffer[y*m_width*4 + x*4 + 3] 
    };
}

void Texture::setPixel(int x, int y, glm::u8vec4 color)
{
// #if DEBUG
//     if( x >= m_width - 3 || x < 0 || y >= m_height - 3 || y < 0)
//         std::cout << "Position out of bound in texture \n";
//     if(!m_localBuffer)
//         std::cout << "Local buffer is nullptr \n";
// #endif

    m_localBuffer[4*y*m_width + 4*x + 0] = color.r;
    m_localBuffer[4*y*m_width + 4*x + 1] = color.g;
    m_localBuffer[4*y*m_width + 4*x + 2] = color.b;  
    m_localBuffer[4*y*m_width + 4*x + 3] = color.a;
}  