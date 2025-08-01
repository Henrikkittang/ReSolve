#include"sceneFractal.hpp"

#include<imgui/imgui.h>

#include"core/appContext.hpp"
#include"util/log.hpp"


void SceneFractal::onCreate()
{
   

    glm::vec2 screenSize = (glm::vec2)ctx.window.getSize();

    m_center = glm::dvec2(-0.75, 0.0);
    m_scale = 3.0 / screenSize.y; // Fit vertically
    m_maxIterations = 500;


    ctx.assets.load("./assets/shaders/fractal.shader", m_shaderHandle);
    Ref<Shader> shader = ctx.assets.get<Shader>(m_shaderHandle);
    shader->bind();
    shader->setUniform2d("uCenter", m_center.x, m_center.y);
    shader->setUniform1d("uScale", m_scale);
    shader->setUniform1i("umaxIterations", m_maxIterations);   
    shader->setUniform2f("uResolution", screenSize.x, screenSize.y);   
    shader->unbind();


    float vertecies[] = {
         -1.0f, -1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f,
        -1.0f,  1.0f,
    };     
    m_renderTarget = Renderable(vertecies, 4, 2, PrimitiveType::QUAD);

    

    /*std::vector<float> positions = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f,
        -1.0f,  1.0f,
    };

    size_t vertex_count = positions.size() / 2; // 2 coordinates per vertex
    size_t quad_count = vertex_count / 4; // 4 vertices per quad
    size_t count = quad_count * 6; // 6 indices per quad

    std::vector<uint32_t> indices(count);

    for(size_t i = 0, vertex_index = 0; i < count; i += 6, vertex_index += 4)
    {
        indices[i + 0] = vertex_index + 0;
        indices[i + 1] = vertex_index + 1;
        indices[i + 2] = vertex_index + 2;
        indices[i + 3] = vertex_index + 2;
        indices[i + 4] = vertex_index + 3;
        indices[i + 5] = vertex_index + 0;
    }
    m_ib = IndexBuffer{ indices.data(), static_cast<uint32_t>(count) };

    VertexBuffer vb(positions.data(), static_cast<uint32_t>(positions.size() * sizeof(float)));
    VertexBufferLayout layout; 
    layout.push<float>(2);
    
    m_va.addBuffer(vb, layout);*/
}

void SceneFractal::onActivate() 
{
    Ref<Shader> shader = ctx.assets.get<Shader>(m_shaderHandle);

    shader->bind();
    m_renderTarget.bind();

    // m_va.bind();
    // m_ib.bind();
}
void SceneFractal::onDeactivate() 
{
    Ref<Shader> shader = ctx.assets.get<Shader>(m_shaderHandle);

    shader->unbind();
    m_renderTarget.unbind();

    // m_va.unbind();
    // m_ib.unbind();
}

void SceneFractal::onUpdate() 
{    
    if (ctx.window.isKeyPressed(GLFW_KEY_UP))
        m_scale *= 0.99; // Zoom in
    if (ctx.window.isKeyPressed(GLFW_KEY_DOWN))
        m_scale /= 0.99; // Zoom out

    // Pan (move center in world space)
    double panStep = 1.0 * m_scale;

    if (ctx.window.isKeyPressed(GLFW_KEY_W))
        m_center.y += panStep;
    if (ctx.window.isKeyPressed(GLFW_KEY_S))
        m_center.y -= panStep;
    if (ctx.window.isKeyPressed(GLFW_KEY_A))
        m_center.x -= panStep;
    if (ctx.window.isKeyPressed(GLFW_KEY_D))
        m_center.x += panStep;

    Ref<Shader> shader = ctx.assets.get<Shader>(m_shaderHandle);
    shader->bind();
    shader->setUniform2d("uCenter", m_center.x, m_center.y);
    shader->setUniform1d("uScale", m_scale);
    shader->setUniform1i("umaxIterations", m_maxIterations);   
    shader->unbind();
}

void SceneFractal::onRender() 
{
    // Ref<Shader> shader = ctx.assets.get<Shader>(m_shaderHandle);

    // shader->bind();
    // m_va.bind();
    // m_ib.bind();

    Ref<Shader> shader = ctx.assets.get<Shader>(m_shaderHandle);
    ctx.window.draw(m_renderTarget, shader);

    
    // GLCall( glDrawElements(GL_TRIANGLES, m_ib.getCount(), GL_UNSIGNED_INT, nullptr) );

    // shader->unbind();
    // m_va.unbind();
    // m_ib.unbind();
}

void SceneFractal::onImGuiRender() 
{
    ImGui::DragInt("Max iterations", &m_maxIterations, 100, 5, 3000);
}


