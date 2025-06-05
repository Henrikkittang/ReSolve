
#include"resourceManager.hpp"


#include<filesystem>
#include<functional>

ResourceManager::ResourceManager()
{}

ResourceManager::~ResourceManager()
{}

bool ResourceManager::load(const std::string& filePathString, ResourceHandle& handle)
{   
    FilePath filepath{filePathString};


    uint32_t id = std::hash<std::string>{}(filepath.string());
    std::string extension = filepath.extension().string();

    
    auto [type, resFunc] = getType(extension);
    if( type == ResourceType::NON )
        return false; // Manager does not support this file type

    if( m_resources.contains(id) )
    {
        handle.filepath = filepath;
        handle.id       = id;
        handle.type     = type;
        return true;  // Resource already loaded and cached
    }

    Ref<Resource> resource = resFunc();
    if(!resource->load(filepath.string()))
        return false;  // Resource failed to load
    

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

bool ResourceManager::reload(const ResourceHandle& handle)
{
#ifdef DEBUG
    if( !m_resources.contains(handle.id) ) 
        std::cout << "Resource not found in unload " << handle.filepath << "\n";       
#endif

    Ref<Resource> resource = m_resources[handle.id];
    resource->unload();

    return resource->load(handle.filepath.string());
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

//////////////
// Private //
//////////////

std::pair<ResourceType, FuncRef<Resource>> ResourceManager::getType(const std::string& extension)
{
    if( m_types.contains( extension ) )
        return m_types[extension];
    return { ResourceType::NON, []() -> Ref<Resource> { return nullptr; }};
}
