#include "resource_manager.h"

namespace lab4::resource
{

std::shared_ptr<FileHandle> ResourceManager::get(const std::string& path)
{
    auto it = cache_.find(path);
    if (it != cache_.end())
    {
        return it->second;
    }

    auto handle = std::make_shared<FileHandle>(path);

    cache_[path] = handle;
    return handle;
}

void ResourceManager::clear()
{
    cache_.clear();
}

bool ResourceManager::contains(const std::string& path) const
{
    return cache_.find(path) != cache_.end();
}

} // namespace lab4::resource