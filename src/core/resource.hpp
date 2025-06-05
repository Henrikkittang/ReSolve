#pragma once
#include<string>
#include<cstdint>
#include<filesystem>


using FilePath = std::filesystem::path;

enum class ResourceType : uint8_t
{
    NON, SHD, TEX
};

struct ResourceHandle
{
    FilePath     filepath = "";
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