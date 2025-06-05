#pragma once
#include<string>
#include<cstdint>
#include<filesystem>


using FilePath = std::filesystem::path;

enum class AssetType : uint8_t
{
    NON, SHD, TEX
};

struct AssetHandle
{
    FilePath     filepath = "";
    uint32_t     id       = 0;
    AssetType type     = AssetType::NON;
};


class Asset
{
public:
    virtual ~Asset(){}
    virtual bool load(const std::string& filepath)   = 0;
    virtual bool unload() = 0;
};