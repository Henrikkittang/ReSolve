#pragma once

namespace test
{
    class Test
    {
    public:
        Test(/* args */) {}
        virtual ~Test() {}
        virtual void onUpdate(float dt) {}
        virtual void onRender() {}
        virtual void onImGuiRender() {}
    };
} // namespace test
