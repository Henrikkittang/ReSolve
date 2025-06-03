#pragma once
#include<unordered_map>

#include"core/resource.hpp"
#include"graphics/texture.hpp"
#include"graphics/shader.hpp"



class ResourceManager
{

public:
    ResourceManager();
    ~ResourceManager();
    ResourceManager(const ResourceManager& other) = delete;
    ResourceManager operator=(const ResourceManager& other) = delete;

    bool load(const std::string& filepath, ResourceHandle* handle);
    bool unload(const ResourceHandle& handle);
    const void* get(const ResourceHandle& handle);
    bool contains(const ResourceHandle& handle);

private:

    std::unordered_map<uint32_t, const void*> m_resources;
};



