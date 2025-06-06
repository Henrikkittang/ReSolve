#include"sceneNoise.hpp"

#include<imgui/imgui.h>
#include"core/camera.hpp"
#include"core/appContext.hpp"
#include"core/asset.hpp"
#include"graphics/texture.hpp"

void SceneNoise::onCreate() 
{
    m_camera = Camera{960.0, 540.0};

    ctx.assets.load("./assets/shaders/basic.shader", m_shaderHandle);
    Ref<Shader> shader = ctx.assets.get<Shader>(m_shaderHandle);

    // m_shader = Shader{};
    // m_shader.load("./assets/shaders/basic.shader");
    auto mvp = m_camera.getMVP();
    shader->bind();
    shader->setUniformMat4f("uMVP", mvp);

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
    shader->setUniform1i("uTexture", 0);

    m_noiseSettnigns.redraw = true;
}

void SceneNoise::onUpdate(  ) 
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

void SceneNoise::onRender(  ) 
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

    Ref<Shader> shader = ctx.assets.get<Shader>(m_shaderHandle);
    shader->bind();
    va.bind();
    ib.bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
    shader->unbind();
    va.unbind();
    ib.unbind();
}

void SceneNoise::onImGuiRender() 
{
    m_noiseSettnigns.redraw = ImGui::Button("Redraw");
    
    ImGui::DragInt("Depth", &m_noiseSettnigns.depth, 1, 1, 12);
    ImGui::DragFloat("Amplitude", &m_noiseSettnigns.amp, 0.5, 1, 20);    
    ImGui::DragFloat("Frequency", &m_noiseSettnigns.freq, 0.5, 1, 20);    
};


void SceneNoise::onActivate() 
{

}

void SceneNoise::onDeactivate() 
{}
