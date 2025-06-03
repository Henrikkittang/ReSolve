
#include<string>
#include<cstdint>


enum class ResourceType
{
    TEX, SHD, WAV
};

struct ResourceHandle
{
    std::string  filepath;
    uint32_t     id;
    ResourceType type;
};
