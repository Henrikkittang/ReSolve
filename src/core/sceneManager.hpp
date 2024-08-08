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
        if( m_scenes.contains(name) )
            std::cout << "Scene label already used: " << name << "\n";
        m_scenes[name] = new T{};
    }
    
    void removeScene(const std::string& name);
    Scene* getCurrentScene();
    void   setCurrentScene(const std::string& name);
    std::vector<std::string> getNames() const;
    std::vector<Scene*>      getScenes();
  
private:

    // Few elements and having this structure own the scenes means a regular map is best
    std::map<std::string, Scene*> m_scenes;
    Scene* m_currentScene;

};