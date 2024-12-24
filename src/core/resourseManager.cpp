/*
#include"resourseManager.hpp"

ResourseManager::ResourseManager()
{
}

ResourseManager::~ResourseManager()
{
}

bool ResourseManager::loadTexture(const std::string& filepath, ResourceHandle* handle)
{
    Resource* resource = new Texture{};
    resource->load(filepath);

    std::hash<std::string> hash;
    ResourceHandle newHandle;
    newHandle.resource = resource;
    newHandle.type     = ResourceType::TEX;
    newHandle.filepath = filepath;
    newHandle.hash     = hash(filepath);

    handle = &newHandle;
    m_resources.insert({newHandle.hash, newHandle});

    return true;
}

bool ResourseManager::unload(const ResourceHandle& handle)
{
    m_resources[handle.hash].resource->unload();
    delete m_resources[handle.hash].resource;
    m_resources.erase(handle.hash);

    return true;
}


bool ResourseManager::unload(const ResourceHandle& handle)
{
    m_resources[handle.hash].resource->unload();
    delete m_resources[handle.hash].resource;
    m_resources.erase(handle.hash);
    
    return true;
}

*/
