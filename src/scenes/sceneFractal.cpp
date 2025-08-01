#include"sceneFractal.hpp"

#include<imgui/imgui.h>

#include"core/appContext.hpp"
#include"util/log.hpp"


void SceneFractal::onCreate()
{
    uZoom = 1.0f;
    uPan = {0.0f, 0.0f};
    maxIterations = 500;

    ctx.assets.load("./assets/shaders/fractal.shader", m_shaderHandle);

    glm::ivec2 screenSize = ctx.window.getSize();

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
    if( ctx.window.isKeyPressed(GLFW_KEY_UP) )
        uZoom = uZoom * 0.99;

    if( ctx.window.isKeyPressed(GLFW_KEY_DOWN) )
        uZoom = uZoom / 0.99;

    if( ctx.window.isKeyPressed(GLFW_KEY_W) )
        uPan.y = uPan.y - 0.01 * uZoom;

    if( ctx.window.isKeyPressed(GLFW_KEY_S) )
        uPan.y = uPan.y + 0.01 * uZoom;

    if( ctx.window.isKeyPressed(GLFW_KEY_D) )
        uPan.x = uPan.x - 0.01 * uZoom;

    if( ctx.window.isKeyPressed(GLFW_KEY_A) )
        uPan.x = uPan.x + 0.01 * uZoom;

    Ref<Shader> shader = ctx.assets.get<Shader>(m_shaderHandle);
    shader->bind();
    shader->setUniform1f("uZoom", uZoom);
    shader->setUniform2f("uPan", uPan.x, uPan.y);
    shader->setUniform1i("maxIterations", maxIterations);   
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
    ImGui::DragInt("Max iterations", &maxIterations, 100, 5, 3000);
}


