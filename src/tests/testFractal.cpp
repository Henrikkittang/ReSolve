#include"testFractal.hpp"

#include"../renderer.hpp"

#include<imgui/imgui.h>
 
namespace test
{
    
    TestFractal::TestFractal() 
        :m_vb(nullptr, 0), m_ib(nullptr, 0)
    {
        std::vector<float> positions = {
            -1.0f, -1.0f,  
             1.0f, -1.0f, 
             1.0f,  1.0f, 
            -1.0f,  1.0f, 
        };

        m_vb = VertexBuffer(positions.data(), positions.size() * sizeof(float) );

        

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

        m_ib = IndexBuffer(indices.data(), count);

        VertexBufferLayout layout;
        layout.push<float>(2);


        m_va.addBuffer(m_vb, layout);



        m_shader = Shader{ "./resources/shaders/fractal.shader" };    

        

        m_shader.bind();
        m_shader.setUniform1f("uZoom", uZoom);
        m_shader.setUniform2f("uPan", uPan.x, uPan.y);
        m_shader.setUniform1i("maxIterations", maxIterations);
    }
    
    TestFractal::~TestFractal() 
    {}

    void TestFractal::onUpdate(float dt) {}


    void TestFractal::onUpdate(const Renderer& renderer, float dt) 
    {
        if( glfwGetKey( renderer.getWindow(), GLFW_KEY_UP ) == GLFW_PRESS )
            uZoom = uZoom * 0.99;
        
        if( glfwGetKey( renderer.getWindow(), GLFW_KEY_DOWN ) == GLFW_PRESS )
            uZoom = uZoom / 0.99;

        if( glfwGetKey( renderer.getWindow(), GLFW_KEY_W ) == GLFW_PRESS )
            uPan.y = uPan.y - 0.01 * uZoom;

        if( glfwGetKey( renderer.getWindow(), GLFW_KEY_S ) == GLFW_PRESS )
            uPan.y = uPan.y + 0.01 * uZoom;

        if( glfwGetKey( renderer.getWindow(), GLFW_KEY_D ) == GLFW_PRESS )
            uPan.x = uPan.x - 0.01 * uZoom;

        if( glfwGetKey( renderer.getWindow(), GLFW_KEY_A ) == GLFW_PRESS )
            uPan.x = uPan.x + 0.01 * uZoom;
        
        m_shader.bind();
        m_shader.setUniform1f("uZoom", uZoom);
        m_shader.setUniform2f("uPan", uPan.x, uPan.y);
        m_shader.setUniform1i("maxIterations", maxIterations);
    }


    void TestFractal::onRender() 
    {

    }
    
    void TestFractal::onImGuiRender() 
    {
        ImGui::DragInt("Max iterations", &maxIterations, 100, 5, 30000);
    }
    
} 
