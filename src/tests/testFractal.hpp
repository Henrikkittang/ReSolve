#pragma once

#include "test.hpp"

#include"vertexArray.hpp"
#include"vertexBuffer.hpp"
#include"indexBuffer.hpp"
#include"shader.hpp"
#include"renderer.hpp"

namespace test
{
    class TestFractal : public Test 
    {
    public:
        TestFractal(/* args */);
        ~TestFractal();
        void onUpdate(float dt) override;
        void onRender() override;
        void onImGuiRender() override;

        void onUpdate(const Renderer& renderer, float dt);

    private:
        VertexArray  m_va;
        VertexBuffer m_vb;
        IndexBuffer  m_ib;
        Shader       m_shader;

        float uZoom    = 1.0f;            
        glm::vec2 uPan = {0.0f, 0.0f};      
        int maxIterations = 500;
    };
} // namespace test
