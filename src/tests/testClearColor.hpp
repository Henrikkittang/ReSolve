#pragma once

#include "test.hpp"



namespace test
{
    class TestClearColor : public Test 
    {
    public:
        TestClearColor(/* args */);
        ~TestClearColor();
        void onUpdate( const RenderWindow& wn, float dt) override;
        void onRender( const RenderWindow& wn, float dt ) override;
        void onImGuiRender() override;
    private:
        float m_clearColor[4];
    };
} // namespace test
