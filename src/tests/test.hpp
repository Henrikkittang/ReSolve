#pragma once

#include"../renderWindow.hpp"

namespace test
{
    class Test
    {
    public:
        Test(/* args */) {}
        virtual ~Test() {}
        virtual void onUpdate( const RenderWindow& wn, float dt) {}
        virtual void onRender() {}
        virtual void onImGuiRender() {}
    };
} // namespace test
