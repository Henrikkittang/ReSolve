#include"sceneManager.hpp"
#include<iostream>


SceneManager::SceneManager()
    : m_scenes(), m_currentScene(nullptr)
{}


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
    m_currentScene->onActive();
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

