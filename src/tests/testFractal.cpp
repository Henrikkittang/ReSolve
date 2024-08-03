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

        m_positions = {
            0.1f, 0.1f,  
            0.2f, 0.1f, 
            0.2f, 0.2f, 
            0.1f, 0.2f, 

            0.3f, 0.3f,  
            0.4f, 0.3f, 
            0.4f, 0.4f, 
            0.3f, 0.4f, 
        };

        m_vb = VertexBuffer{ m_positions.data(), static_cast<uint32_t>(m_positions.size() * sizeof(float)) };
        
        size_t vertex_count = m_positions.size() / 2; // 2 coordinates per vertex
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

        m_layout.push<float>(2);
        
        m_va.addBuffer(m_vb, m_layout);


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

        
       

        auto vb = VertexBuffer{ m_positions.data(), static_cast<uint32_t>(m_positions.size() * sizeof(float)) };
        vb.bind();
        // m_vb.bind(); // Should work instead of the two lines above

        m_va.bind();
        GLCall( glEnableVertexAttribArray(0) );
        GLCall( glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8, (const void*)0) );

        m_shader.bind();
        m_va.bind();
        m_ib.bind();
        
        GLCall(glDrawElements(GL_TRIANGLES, m_ib.getCount(), GL_UNSIGNED_INT, nullptr));

        m_shader.unbind();
        m_va.unbind();
        m_ib.unbind();

        wn.draw(m_va, m_ib, m_shader);

    }


    void TestFractal::onRender() 
    {

    }
    
    void TestFractal::onImGuiRender() 
    {
        ImGui::DragInt("Max iterations", &maxIterations, 100, 5, 3000);
    }
    
} 
