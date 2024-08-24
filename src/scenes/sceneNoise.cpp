#include"sceneNoise.hpp"

#include<imgui/imgui.h>

#include"texture.hpp"

void SceneNoise::init() 
{
    m_camera = Camera{960.0, 540.0};

    m_shader = Shader{"./resources/shaders/basic.shader"};
    auto mvp = m_camera.getMVP();
    m_shader.bind();
    m_shader.setUniformMat4f("uMVP", mvp);

    m_texture = Texture{960, 540};
    
    for(int y = 0; y < 540; y++)
    {
        for(int x = 0; x < 960; x++)
        {
            double scale = Noise::turbulence((double)x/960, (double)y/540, 0, m_noiseSettnigns.depth) ;
            scale = m_noiseSettnigns.amp * sin(m_noiseSettnigns.freq*scale);
            
            glm::u8 color = static_cast<glm::u8>(255*scale);
            m_texture.setPixel(x, y, glm::u8vec4(color, color, 0, 255));  
        }
    }
    m_texture.update();
    m_texture.bind();
    m_shader.setUniform1i("uTexture", 0);

    m_noiseSettnigns.redraw = true;
}

void SceneNoise::onUpdate( const RenderWindow& wn ) 
{
    if( !m_noiseSettnigns.redraw )
        return;
    
    for(int y = 0; y < 540; y++)
    {
        for(int x = 0; x < 960; x++)
        {
            double scale = Noise::turbulence((double)x/960, (double)y/540, 0, m_noiseSettnigns.depth) ;
            scale = m_noiseSettnigns.amp * sin(m_noiseSettnigns.freq*scale);
            
            glm::u8 color = static_cast<glm::u8>(255*scale);
            m_texture.setPixel(x, y, glm::u8vec4(color, color, 0, 255));  
        }
    }
    m_texture.update();
    m_texture.bind();

    m_noiseSettnigns.redraw = false;
}

void SceneNoise::onRender( const RenderWindow& wn ) 
{
    float positions[] = {
          0.0f,    0.0f, 0.0f, 0.0f,
        960.0f,    0.0f, 1.0f, 0.0f,
        960.0f,  540.0f, 1.0f, 1.0f,
          0.0f,  540.0f, 0.0f, 1.0f,
    };
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    unsigned int indices[] = {  // Note that we start from 0!
        0, 1, 2,
        2, 3, 0
    };
    IndexBuffer ib(indices, 6);

    VertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(2);

    VertexArray va;
    va.addBuffer(vb, layout);

    m_texture.bind();

    wn.draw(va, ib, m_shader);   
}

void SceneNoise::onImGuiRender() 
{
    m_noiseSettnigns.redraw = ImGui::Button("Redraw");
    
    ImGui::DragInt("Depth", &m_noiseSettnigns.depth, 1, 1, 12);
    ImGui::DragFloat("Amplitude", &m_noiseSettnigns.amp, 0.5, 1, 20);    
    ImGui::DragFloat("Frequency", &m_noiseSettnigns.freq, 0.5, 1, 20);    
};


void SceneNoise::onActive() 
{}

void SceneNoise::onDeactivate() 
{}
