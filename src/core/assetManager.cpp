
#include"core/assetManager.hpp"


#include<filesystem>
#include<functional>

#include"util/util.hpp"

AssetManager::AssetManager()
{}

AssetManager::~AssetManager()
{}

bool AssetManager::load(const std::string& filePathString, AssetHandle& handle)
{   
    FilePath filepath{filePathString};


    uint32_t id = std::hash<std::string>{}(filepath.string());
    std::string extension = filepath.extension().string();

    
    auto [type, resFunc] = getType(extension);
    if( type == AssetType::NON )
        return false; // Manager does not support this file type

    if( m_assets.contains(id) )
    {
        handle.filepath = filepath;
        handle.id       = id;
        handle.type     = type;
        return true;  // asset already loaded and cached
    }

    Ref<Asset> asset = resFunc();
    if(!asset->load(filepath.string()))
        return false;  // asset failed to load
    

    handle.filepath = filepath;
    handle.id       = id;
    handle.type     = type;

    m_assets[handle.id] = asset;

    return true;
}

bool AssetManager::unload(AssetHandle& handle)
{
    DEBUG_CHECK(!m_assets.contains(handle.id), "Asset not found in unload " + handle.filepath.string());
    
    Ref<Asset> asset = m_assets[handle.id];
    m_assets.erase(handle.id);
    asset->unload();

    handle.filepath = "";
    handle.id       = 0;
    handle.type     = AssetType::NON;

    return true;
}

bool AssetManager::reload(const AssetHandle& handle)
{
    DEBUG_CHECK(!m_assets.contains(handle.id), "Asset not found in reload " + handle.filepath.string());

    Ref<Asset> asset = m_assets[handle.id];
    asset->unload();

    return asset->load(handle.filepath.string());
}

Ref<Asset> AssetManager::get(const AssetHandle& handle) 
{
    DEBUG_CHECK(!m_assets.contains(handle.id), "Asset not found in get " + handle.filepath.string());
    return m_assets[handle.id];
}

bool AssetManager::isValid(const AssetHandle& handle)
{
    return m_assets.contains(handle.id);
}

//////////////
// Private //
//////////////

std::pair<AssetType, FuncRef<Asset>> AssetManager::getType(const std::string& extension)
{
    if( m_types.contains( extension ) )
        return m_types[extension];
    return { AssetType::NON, []() -> Ref<Asset> { return nullptr; }};
}
