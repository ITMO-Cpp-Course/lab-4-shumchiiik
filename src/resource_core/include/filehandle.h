#pragma once
#include <fstream>
#include <string>

namespace lab4::resource
{
class FileHandle
{
  public:
    explicit FileHandle(const std::string& path);

    ~FileHandle() noexcept;

    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;

    FileHandle(FileHandle&& other) noexcept;
    FileHandle& operator=(FileHandle&& other) noexcept;

    std::ifstream& stream()
    {
        return file_;
    }
    bool isOpen() const
    {
        return file_.is_open();
    }
    const std::string& path() const
    {
        return path_;
    }

  private:
    std::ifstream file_;
    std::string path_;
};
} // namespace lab4::resource