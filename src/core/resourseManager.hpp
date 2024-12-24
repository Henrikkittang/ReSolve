/*#pragma once
#include<unordered_map>
#include<string>
#include<functional>

#include"graphics/texture.hpp"
#include"graphics/shader.hpp"



class Resource
{
public:
    bool virtual load(const std::string& filepath) = 0;
    bool virtual unload() = 0;

};

enum class ResourceType
{
    TEX, SHD, WAV
};

struct ResourceHandle
{
    std::string  filepath;
    uint32_t     hash;
    ResourceType type;
    Resource*    resource;
};


class ResourseManager
{

public:
    ResourseManager();
    ~ResourseManager();

    bool loadTexture(const std::string& filepath);

    bool unload(const ResourceHandle& handle);
    ResourceHandle* get(const ResourceHandle& handle);

private:

    std::unordered_map<uint32_t, ResourceHandle> m_resources;
};



*/