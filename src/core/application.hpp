#pragma once    
#include<string>
#include<vector>
#include<stack>

#include<glad/glad.h>


#include"core/appContext.hpp"
#include"core/scene.hpp"
#include"core/sceneManager.hpp"
#include"core/assetManager.hpp"
#include"graphics/renderWindow.hpp"


class Application
{
public:
    Application(uint32_t screenWidth, uint32_t screenHeight, const std::string& title);
    ~Application();

    template<typename T>
    inline void registerScene(const std::string& name)
    {
        Scene* scene = new T{m_appContext};
        m_sceneManager.addScene(name, scene);
    }
    
    void ImGuiInit();
    void run();
    
private:

    // NB! The order her may be kinda important since in dictates the order of destruction
    RenderWindow    m_window;
    SceneManager    m_sceneManager;
    AssetManager    m_AssetManager;
    bool            m_isImguiActive;

    // Important that these are defined in the same way as in the struct
    AppContext m_appContext = 
    {
        m_window,
        m_sceneManager,
        m_AssetManager
    };
};
