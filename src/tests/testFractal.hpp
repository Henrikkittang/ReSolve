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
        VertexArray  m_va;
        VertexBuffer m_vb;
        IndexBuffer  m_ib;
        Shader       m_shader;

        std::vector<float> m_positions;
        VertexBufferLayout m_layout;

        float     uZoom;                   
        glm::vec2 uPan;               
        int       maxIterations;
    };
} 
