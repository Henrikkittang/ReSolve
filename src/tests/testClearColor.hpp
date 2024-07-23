#pragma once

#include "test.hpp"



namespace test
{
    class TestClearColor : public Test 
    {
    public:
        TestClearColor(/* args */);
        ~TestClearColor();
        void onUpdate(float dt) override;
        void onRender() override;
        void onImGuiRender() override;
    private:
        float m_clearColor[4];
    };
} // namespace test
