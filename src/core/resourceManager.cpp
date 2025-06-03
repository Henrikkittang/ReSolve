
#include"resourceManager.hpp"

#include<filesystem>

#include"util/random.hpp"

ResourceManager::ResourceManager()
{}

ResourceManager::~ResourceManager()
{}

bool ResourceManager::load(const std::string& filepath, ResourceHandle* handle)
{
    std::filesystem::path pathObject(filepath);
    std::string extension =  pathObject.extension().string();
    
    void* resource;
    if( extension ==  ".shader")
    {
        resource = (void*)new Shader{filepath};
        handle->type = ResourceType::SHD; 
    }
    else if( extension == ".png" )
    {
        resource = (void*)new Texture{filepath};
        handle->type = ResourceType::TEX; 
    }

    handle->filepath = filepath;
    handle->id = Random::getInt();

    m_resources[handle->id] = resource;

    return true;
}

bool ResourceManager::unload(const ResourceHandle& handle)
{
    const void* resource = m_resources[handle.id];
    m_resources.erase(handle.id);
    delete resource;
}

const void* ResourceManager::get(const ResourceHandle& handle) 
{
    return m_resources[handle.id];
}

bool ResourceManager::contains(const ResourceHandle& handle)
{
    return m_resources.contains(handle.id);
}
