
#include <catch2/catch_all.hpp>

#include <filesystem>
#include <fstream>
#include <memory>
#include <string>

#include "../src/resource_core/include/filehandle.h"
#include "../src/resource_core/include/resource_error.h"
#include "../src/resource_core/include/resource_manager.h"

namespace fs = std::filesystem;

const std::string TEST_FILE = "test_lab4.txt";
const std::string CONTENT = "Test Data 123";

void createFile(const std::string& path)
{
    std::ofstream out(path);
    REQUIRE(out.is_open());
    out << CONTENT;
}

void removeFile(const std::string& path)
{
    if (fs::exists(path))
    {
        fs::remove(path);
    }
}

TEST_CASE()
{
    try
    {
        throw lab4::resource::ResourceError("My Error");
    }
    catch (const std::runtime_error& e)
    {
        CHECK(std::string(e.what()) == "My Error");
    }
}

TEST_CASE()
{
    createFile(TEST_FILE);

    {
        lab4::resource::FileHandle fh(TEST_FILE);
        CHECK(fh.isOpen());
        CHECK(fh.path() == TEST_FILE);

        std::string data;
        fh.stream() >> data;
        CHECK(data == "Test");
    }

    removeFile(TEST_FILE);
    CHECK(!fs::exists(TEST_FILE));
}

TEST_CASE()
{
    createFile(TEST_FILE);

    {
        lab4::resource::ResourceManager mgr;

        auto ptr1 = mgr.get(TEST_FILE);
        CHECK(mgr.contains(TEST_FILE));
        CHECK(ptr1->isOpen());

        auto ptr2 = mgr.get(TEST_FILE);

        CHECK(ptr1.get() == ptr2.get());
    }

    removeFile(TEST_FILE);
}
