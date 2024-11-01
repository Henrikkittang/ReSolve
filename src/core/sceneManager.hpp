#pragma once
#include<map>
#include<string>
#include<vector>
#include<variant>

#include"scene.hpp"

class SceneManager
{
public:

    SceneManager();

    template<typename T>
    inline void addScene(const std::string& name)
    {
#if DEBUG
        if( m_scenes.contains(name) )
            std::cout << "Scene label already used: " << name << "\n";
#endif 
        m_scenes[name] = new T{};
        m_scenes[name]->onCreate();
    }
    
    void   removeScene(const std::string& name);
    Scene* getCurrentScene();
    void   setCurrentScene(const std::string& name);
    std::vector<std::string> getNames() const;
    std::vector<Scene*>      getScenes();
  
private:

    std::map<std::string, Scene*> m_scenes;
    Scene* m_currentScene;

};