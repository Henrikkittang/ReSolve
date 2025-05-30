#pragma once
#include<map>
#include<string>
#include<vector>
#include<variant>

#include"core/scene.hpp"

class SceneManager
{
public:

    SceneManager();
    ~SceneManager();

    void addScene(const std::string& name, Scene* scene);
    void removeScene(const std::string& name);
    Scene* getCurrentScene();
    void   setCurrentScene(const std::string& name);
    std::vector<std::string> getNames() const;
    std::vector<Scene*>      getScenes();
  
private:

    std::map<std::string, Scene*> m_scenes;
    Scene* m_currentScene;

};