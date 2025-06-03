#pragma once
#include<string>
#include<cstdint>



enum class ResourceType
{
    NON, SHD, TEX
};

struct ResourceHandle
{
    std::string  filepath = "";
    uint32_t     id       = 0;
    ResourceType type     = ResourceType::NON;
};


class Resource
{
public:
    virtual ~Resource(){}
    virtual bool load(const std::string& filepath)   = 0;
    virtual bool unload() = 0;
};