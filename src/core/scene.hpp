#pragma once
#include<iostream>
#include<cassert>


struct AppContext; 


class Scene
{
public:
    
    inline Scene(AppContext& ctx) 
        : ctx(ctx)
    {}

    virtual ~Scene() {}

    virtual void onCreate() { assert("Init not implemented"); }
    virtual void onDestroy() {}

    virtual void onUpdate() { assert("OnUpdate not implemented");  }
    virtual void onRender() { assert("OnRender not implemented");  }
    virtual void onImGuiRender() {};

    virtual void onActivate() {}
    virtual void onDeactivate() {}
    
    // virtual void onEvent(Event event);

protected: 

    AppContext& ctx;

};
