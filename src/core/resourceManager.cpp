
#include"resourceManager.hpp"

#include<filesystem>
#include<functional>

ResourceManager::ResourceManager()
{}

ResourceManager::~ResourceManager()
{}

bool ResourceManager::load(const std::string& filepath, ResourceHandle& handle)
{
    uint32_t id = std::hash<std::string>{}(filepath);

    // if( m_resources.contains(id) ) // maybe add something like smart pointer func to the handles
 
    std::string extension = std::filesystem::path(filepath).extension().string();

    Ref<Resource> resource;
    ResourceType type;
    if( extension ==  ".shader")
    {
        resource = std::make_shared<Shader>();
        type = ResourceType::SHD; 
    }
    else if( extension == ".png" )
    {
        resource = std::make_shared<Texture>();
        type = ResourceType::TEX; 
    }
    else
        return false;

    if(!resource->load(filepath))
        return false;
    

    handle.filepath = filepath;
    handle.id       = id;
    handle.type     = type;

    m_resources[handle.id] = resource;

    return true;
}

bool ResourceManager::unload(ResourceHandle& handle)
{
#ifdef DEBUG
    if( !m_resources.contains(handle.id) ) 
        std::cout << "Resource not found in unload " << handle.filepath << "\n";       
#endif
    
    Ref<Resource> resource = m_resources[handle.id];
    m_resources.erase(handle.id);
    resource->unload();

    handle.filepath = "";
    handle.id       = 0;
    handle.type     = ResourceType::NON;

    return true;
}

Ref<Resource> ResourceManager::get(const ResourceHandle& handle) 
{
#ifdef DEBUG
    if( !m_resources.contains(handle.id) ) 
        std::cout << "Resource not found in get " << handle.filepath << "\n";       
#endif

    return m_resources[handle.id];
}

bool ResourceManager::isValid(const ResourceHandle& handle)
{
    return m_resources.contains(handle.id);
}
