#include "../include/storage-file.h"

#include <filesystem>
#include <fstream>
#include <sstream>

StorageFile::StorageFile(std::string path) : _path(std::move(path))
{
    InitializeStorage();
}

void StorageFile::WriteJson(const std::string& json) const
{
    std::ofstream out;

    out.open(_path);

    if (!out.is_open())
        throw std::filesystem::filesystem_error("Cannot open the storage file.", std::error_code());

    out << json;
}

std::string StorageFile::ReadJson() const
{
    std::ifstream in;

    in.open(_path);

    if (!in.is_open())
        throw std::filesystem::filesystem_error("Cannot open the storage file.", std::error_code());

    std::stringstream buffer;
    buffer << in.rdbuf();

    return buffer.str();
}

void StorageFile::InitializeStorage() const
{
    if (!std::filesystem::exists(_path))
    {
        std::ofstream storageFile(_path);

        if (!storageFile)
            throw std::filesystem::filesystem_error("Cannot create the storage file.", std::error_code());
    }
}