#include<iostream>
#include"core/sceneManager.hpp"
#include"util/log.hpp"

SceneManager::SceneManager()
    : m_scenes(), m_currentScene(nullptr)
{}

SceneManager::~SceneManager()
{
    if(m_currentScene != nullptr)
        m_currentScene->onDeactivate();
 
    for (const auto& [name, scene] : m_scenes) 
    {
        scene->onDestroy();
        delete scene;
    }
}

void SceneManager::addScene(const std::string& name, Scene* scene)
{
    CHECK_WARN(m_scenes.contains(name), "Scene label already used: " + name);

    scene->onCreate();
    m_scenes[name] = scene;
}

void SceneManager::removeScene(const std::string& name)
{
    CHECK_FATAL(m_scenes.contains(name), "Cant remove scene because name not in scenes: " + name);


    auto it = m_scenes.find(name);
    m_scenes.erase(name);
    delete it->second;
}

Scene* SceneManager::getCurrentScene()
{   
    CHECK_WARN(m_currentScene == nullptr, "Current scene is nullptr");

    return m_currentScene;
}

void SceneManager::setCurrentScene(const std::string& name)
{
    CHECK_WARN(m_scenes.contains(name), "Cant set scene because name not in scenes: " + name);

    if( m_currentScene )
        m_currentScene->onDeactivate();

    m_currentScene = m_scenes[name];
    m_currentScene->onActivate();
}   

std::vector<std::string> SceneManager::getNames() const
{
    std::vector<std::string> names;
    names.reserve( m_scenes.size() );

    for(auto it = m_scenes.begin(); it != m_scenes.end(); it++)
        names.push_back( it->first );

    return names;
}

std::vector<Scene*> SceneManager::getScenes()
{
    std::vector<Scene*> scenes;
    scenes.reserve( m_scenes.size() );

    for(auto it = m_scenes.begin(); it != m_scenes.end(); ++it)
        scenes.push_back( it->second) ;

    return scenes;
}

