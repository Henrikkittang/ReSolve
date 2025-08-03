
#include"core/assetManager.hpp"


#include<filesystem>
#include<functional>

#include"util/log.hpp"

AssetManager::AssetManager()
{}

AssetManager::~AssetManager()
{}

// TODO! Change this to use expected
bool AssetManager::load(const std::string& filePathString, AssetHandle& handle)
{   
    // NB! Not a permanent solution
    FilePath filepath = FilePath(SOURCE_DIR) / FilePath(filePathString);

    uint32_t id = std::hash<std::string>{}(filepath.string());
    std::string extension = filepath.extension().string();

    
    auto [type, resFunc] = getType(extension);
    if( type == AssetType::NON )
    {
        LOG_ERROR("Asset manager does not support files of type {}", extension);
        return false; 
    }


    if( m_assets.contains(id) )
    {
        handle.filepath = filepath;
        handle.id       = id;
        handle.type     = type;
        return true;  // asset already loaded and cached
    }

    Ref<Asset> asset = resFunc();
    if(!asset->load(filepath.string()))
    {
        LOG_ERROR("Asset failed to load: {}", filePathString);
        return false; 
    }
    

    handle.filepath = filepath;
    handle.id       = id;
    handle.type     = type;

    m_assets[handle.id] = asset;

    return true;
}

bool AssetManager::unload(AssetHandle& handle)
{
    CHECK_FATAL(!m_assets.contains(handle.id), "Asset not found in unload " + handle.filepath.string());
    
    Ref<Asset> asset = m_assets[handle.id];
    asset->unload();
    m_assets.erase(handle.id);

    handle.filepath = "";
    handle.id       = 0;
    handle.type     = AssetType::NON;

    return true;
}

bool AssetManager::reload(const AssetHandle& handle)
{
    CHECK_FATAL(!m_assets.contains(handle.id), "Asset not found in reload " + handle.filepath.string());

    Ref<Asset> asset = m_assets[handle.id];
    asset->unload();

    return asset->load(handle.filepath.string());
}

Ref<Asset> AssetManager::get(const AssetHandle& handle) 
{
    CHECK_FATAL(!m_assets.contains(handle.id), "Asset not found in get " + handle.filepath.string());
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
