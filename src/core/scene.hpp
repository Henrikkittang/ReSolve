#pragma once
#include<iostream>
#include<cassert>

#include"renderWindow.hpp"


class Scene
{
public:
    

    inline Scene() { }
    inline ~Scene() { }


    virtual void onCreate() { assert("Init not implemented"); }
    virtual void onDestroy() {}

    virtual void onUpdate( const RenderWindow& wn ) { assert("OnUpdate not implemented");  }
    virtual void onRender( const RenderWindow& wn ) { assert("OnRender not implemented");  }
    virtual void onImGuiRender() {};

    virtual void onActivate() {}
    virtual void onDeactivate() {}
    
    // virtual void onEvent(Event event);

};
