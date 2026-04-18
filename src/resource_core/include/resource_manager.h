#pragma once
#include "filehandle.h"
#include <memory>
#include <string>
#include <unordered_map>

namespace lab4::resource
{
class ResourceManager
{
  public:
    std::shared_ptr<FileHandle> get(const std::string& path);
    void clear();
    bool contains(const std::string& path) const;

  private:
    std::unordered_map<std::string, std::shared_ptr<FileHandle>> cache_;
};
} // namespace lab4::resource