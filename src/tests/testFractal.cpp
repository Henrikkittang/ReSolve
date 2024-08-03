#include"testFractal.hpp"

#include"../renderWindow.hpp"

#include<imgui/imgui.h>
 
#include<iostream>

namespace test
{
    
    TestFractal::TestFractal() 
        : uZoom(1.0f), uPan(0.0f, 0.0f), maxIterations(500), m_shader("./resources/shaders/test.shader")
    {
        // m_shader.bind();
        // m_shader.setUniform1f("uZoom", uZoom);
        // m_shader.setUniform2f("uPan", uPan.x, uPan.y);
        // m_shader.setUniform1i("maxIterations", maxIterations);

        std::vector<float> positions = {
            0.1f, 0.1f,  
            0.2f, 0.1f, 
            0.2f, 0.2f, 
            0.1f, 0.2f, 
        };

        m_vb = VertexBuffer{ positions.data(), static_cast<uint32_t>(positions.size() * sizeof(float)) };

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

        VertexBufferLayout layout;
        layout.push<float>(2);
        
        m_va.addBuffer(m_vb, layout);

        std::cout << "test fractals initilzed \n";
    }
    
    TestFractal::~TestFractal() 
    {}

    void TestFractal::onUpdate(const RenderWindow& wn, float dt) 
    {

        if( wn.isKeyPressed(GLFW_KEY_UP) )
            uZoom = uZoom * 0.99;

        if( wn.isKeyPressed(GLFW_KEY_DOWN) )
            uZoom = uZoom / 0.99;

        if( wn.isKeyPressed(GLFW_KEY_W) )
            uPan.y = uPan.y - 0.01 * uZoom;

        if( wn.isKeyPressed(GLFW_KEY_S) )
            uPan.y = uPan.y + 0.01 * uZoom;

        if( wn.isKeyPressed(GLFW_KEY_D) )
            uPan.x = uPan.x - 0.01 * uZoom;

        if( wn.isKeyPressed(GLFW_KEY_A) )
            uPan.x = uPan.x + 0.01 * uZoom;
        
        // m_shader.bind();
        // m_shader.setUniform1f("uZoom", uZoom);
        // m_shader.setUniform2f("uPan", uPan.x, uPan.y);
        // m_shader.setUniform1i("maxIterations", maxIterations);

        std::vector<float> positions = {
            0.1f, 0.1f,  
            0.2f, 0.1f, 
            0.2f, 0.2f, 
            0.1f, 0.2f, 
        };

       

        auto vb = VertexBuffer{ positions.data(), static_cast<uint32_t>(positions.size() * sizeof(float)) };
        VertexBufferLayout layout;
        layout.push<float>(2);
        
        VertexArray va{};
        va.addBuffer(vb, layout); // Works
        // va.addBuffer(m_vb, layout); // Does not work


        


        wn.draw(va, m_ib, m_shader);
    }


    void TestFractal::onRender() 
    {

    }
    
    void TestFractal::onImGuiRender() 
    {
        ImGui::DragInt("Max iterations", &maxIterations, 100, 5, 3000);
    }
    
} 
