#include "filehandle.h"

#include "resource_error.h"

#include <utility>

namespace lab4::resource
{

FileHandle::FileHandle(const std::string& path) : path_(path)
{
    file_.open(path);
    if (!file_.is_open())
    {
        throw ResourceError("Cannot open file: " + path);
    }
}

FileHandle::~FileHandle() noexcept
{
    if (file_.is_open())
    {
        file_.close();
    }
}

FileHandle::FileHandle(FileHandle&& other) noexcept : file_(std::move(other.file_)), path_(std::move(other.path_)) {}

FileHandle& FileHandle::operator=(FileHandle&& other) noexcept
{
    if (this != &other)
    {
        if (file_.is_open())
            file_.close();
        file_ = std::move(other.file_);
        path_ = std::move(other.path_);
    }
    return *this;
}

} // namespace lab4::resource