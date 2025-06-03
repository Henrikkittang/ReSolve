
#include"resourceManager.hpp"

#include<iostream>
#include<filesystem>

#include"util/random.hpp"


ResourceManager::ResourceManager()
{}

ResourceManager::~ResourceManager()
{}

bool ResourceManager::load(const std::string& filepath, ResourceHandle& handle)
{
    std::filesystem::path pathObject(filepath);
    std::string extension = pathObject.extension().string();
    
    Resource* resource;
    if( extension ==  ".shader")
    {
        resource = (Resource*)new Shader{};
        handle.type = ResourceType::SHD; 
    }
    else if( extension == ".png" )
    {
        resource = (Resource*)new Texture{};
        handle.type = ResourceType::TEX; 
    }
    else
        return false;

    if(!resource->load(filepath));
        return false;

    handle.filepath = filepath;
    handle.id = Random::getInt();

    m_resources[handle.id] = resource;

    return true;
}

bool ResourceManager::unload(ResourceHandle& handle)
{
#ifdef DEBUG
    if( !m_resources.contains(handle.id) ) 
        std::cout << "Resource not found: " << handle.id << "\n";       
#endif
    
    Resource* resource = m_resources[handle.id];
    m_resources.erase(handle.id);

    resource->unload();

    if(handle.type == ResourceType::SHD)
        delete static_cast<Shader*>(resource);
    else if(handle.type == ResourceType::TEX)
        delete static_cast<Texture*>(resource);
    
    handle.filepath = "";
    handle.id       = 0;
    handle.type     = ResourceType::NON;

    return true;
}

Resource* ResourceManager::get(const ResourceHandle& handle) 
{
    return m_resources[handle.id];
}

bool ResourceManager::contains(const ResourceHandle& handle)
{
    return m_resources.contains(handle.id);
}
