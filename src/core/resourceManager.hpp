#pragma once

#include<iostream>
#include<unordered_map>
#include<memory>


#include"core/resource.hpp"
#include"graphics/texture.hpp"
#include"graphics/shader.hpp"


template<typename T>
using Ref = std::shared_ptr<T>;

class ResourceManager
{

public:
    ResourceManager();
    ~ResourceManager();
    ResourceManager(const ResourceManager& other) = delete;
    ResourceManager operator=(const ResourceManager& other) = delete;

    bool load(const std::string& filepath, ResourceHandle& handle);
    bool unload(ResourceHandle& handle);
    Ref<Resource> get(const ResourceHandle& handle);

    template<typename T>
    Ref<T> get(const ResourceHandle& handle)
    {
#ifdef DEBUG
        if( !m_resources.contains(handle.id) ) 
            std::cout << "Resource not found in get " << handle.filepath << "\n";       
#endif
        return std::static_pointer_cast<T>(m_resources[handle.id]);
    }

    bool isValid(const ResourceHandle& handle);

private:

    std::unordered_map<uint32_t, Ref<Resource>> m_resources;
};



