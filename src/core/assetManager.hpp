#pragma once

#include<unordered_map>
#include<memory>
#include<functional>

#include"core/asset.hpp"
#include"graphics/texture.hpp"
#include"graphics/shader.hpp"
#include"util/log.hpp"
    

template<typename T>
using Ref = std::shared_ptr<T>;


template<typename T>
using FuncRef = std::function<Ref<T>()>;

class AssetManager
{

public:
    AssetManager();
    ~AssetManager();
    AssetManager(const AssetManager& other) = delete;
    AssetManager operator=(const AssetManager& other) = delete;

    bool load(const std::string& filepath, AssetHandle& handle);
    bool unload(AssetHandle& handle);
    bool reload(const AssetHandle& handle);
    Ref<Asset> get(const AssetHandle& handle);

    template<typename T>
    Ref<T> get(const AssetHandle& handle)
    {
        CHECK_FATAL(!m_assets.contains(handle.id), "Resource not found in get " + handle.filepath.string());
        return std::static_pointer_cast<T>(m_assets[handle.id]);
    }

    bool isValid(const AssetHandle& handle);

private:
    std::pair<AssetType, FuncRef<Asset>> getType(const std::string& extension);

private:

    std::unordered_map<uint32_t, Ref<Asset>> m_assets;

    std::unordered_map<std::string, std::pair<AssetType, FuncRef<Asset>>  > m_types = {
        {".png",     {AssetType::TEX, []() { return std::make_shared<Texture>(); }}},
        {".jpg",     {AssetType::TEX, []() { return std::make_shared<Texture>(); }}},
        {".jpeg",    {AssetType::TEX, []() { return std::make_shared<Texture>(); }}},
        {".shader",  {AssetType::SHD, []() { return std::make_shared<Shader>();  }}},
    };
};



