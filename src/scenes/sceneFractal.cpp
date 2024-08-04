#include"sceneFractal.hpp"

#include<iostream>

#include<imgui/imgui.h>

#include"util.hpp"

    
SceneFractal::SceneFractal() 
    : uZoom(1.0f), uPan(0.0f, 0.0f), maxIterations(500)
{
    m_shader = Shader{"./resources/shaders/fractal.shader"};

    std::vector<float> positions = {
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
    
    m_va.addBuffer(vb, layout);
}

SceneFractal::~SceneFractal() 
{}

void SceneFractal::onUpdate(GLFWwindow* wn) 
{    
    m_shader.bind();
    m_shader.setUniform1f("uZoom", uZoom);
    m_shader.setUniform2f("uPan", uPan.x, uPan.y);
    m_shader.setUniform1i("maxIterations", maxIterations);   
    
}

void SceneFractal::onRender(GLFWwindow* wn) 
{
    m_shader.bind();
    m_va.bind();
    m_ib.bind();
    
    GLCall(glDrawElements(GL_TRIANGLES, m_ib.getCount(), GL_UNSIGNED_INT, nullptr));

    m_shader.unbind();
    m_va.unbind();
    m_ib.unbind();
}

void SceneFractal::onImGuiRender() 
{
    ImGui::DragInt("Max iterations", &maxIterations, 100, 5, 3000);
}


