#pragma once

#include<iostream>
#include<unordered_map>
#include<memory>
#include<functional>

#include"core/resource.hpp"
#include"graphics/texture.hpp"
#include"graphics/shader.hpp"


template<typename T>
using Ref = std::shared_ptr<T>;


template<typename T>
using FuncRef = std::function<Ref<T>()>;

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
    std::pair<ResourceType, FuncRef<Resource>> getType(const std::string& extension);

private:

    std::unordered_map<uint32_t, Ref<Resource>> m_resources;

    std::unordered_map<std::string, std::pair<ResourceType, FuncRef<Resource>>  > m_types = {
        {".png",     {ResourceType::TEX, []() { return std::make_shared<Texture>(); }}},
        {".jpg",     {ResourceType::TEX, []() { return std::make_shared<Texture>(); }}},
        {".jpeg",    {ResourceType::TEX, []() { return std::make_shared<Texture>(); }}},
        {".shader",  {ResourceType::SHD, []() { return std::make_shared<Shader>();  }}},
    };
};



