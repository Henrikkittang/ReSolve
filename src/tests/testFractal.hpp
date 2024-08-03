#pragma once

#include "test.hpp"

#include"../vertexArray.hpp"
#include"../vertexBuffer.hpp"
#include"../indexBuffer.hpp"
#include"../shader.hpp"
#include"../renderWindow.hpp"

namespace test
{
    class TestFractal : public Test 
    {
    public:
        TestFractal();
        ~TestFractal();
        void onUpdate(const RenderWindow& wn, float dt) override;
        void onRender() override;
        void onImGuiRender() override;


    private:
        float        uZoom;                   
        glm::vec2    uPan;               
        int          maxIterations;
        Shader       m_shader;
        std::vector<float> m_positions;
        VertexBuffer m_vb;

        VertexArray  m_va;
        IndexBuffer  m_ib;

        VertexBufferLayout m_layout;

        
    };
} 
