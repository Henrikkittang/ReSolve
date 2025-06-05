#include<iostream>
#include"core/sceneManager.hpp"


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
#if DEBUG
    if( m_scenes.contains(name) )
        std::cout << "Scene label already used: " << name << "\n";
#endif 
    scene->onCreate();
    m_scenes[name] = scene;
}

void SceneManager::removeScene(const std::string& name)
{
#if DEBUG
    if( !m_scenes.contains( name ) )
        std::cout << "Cant remove scene because name not in scenes: "<< name << "\n";
#endif

    auto it = m_scenes.find(name);
    m_scenes.erase(name);
    delete it->second;
}

Scene* SceneManager::getCurrentScene()
{
#if DEBUG
    if(m_currentScene == nullptr)
        std::cout << "Current scene is nullptr \n";
#endif   
    return m_currentScene;
}

void SceneManager::setCurrentScene(const std::string& name)
{
#if DEBUG
    if( !m_scenes.contains( name ) )
        std::cout << "Cant set scene because name not in scenes: "<< name << "\n";
#endif    

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

