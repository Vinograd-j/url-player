#include "../include/storage-file.h"

#include <filesystem>
#include <fstream>
#include <sstream>

StorageFile::StorageFile(std::string path) : _path(std::move(path))
{
    InitializeStorage();
}

void StorageFile::RewriteJson(const std::string& json) const
{
    std::ofstream out;

    out.open(_path, std::ofstream::out | std::ofstream::trunc);

    if (!out.is_open())
        throw std::filesystem::filesystem_error("Cannot open the storage file.", std::error_code());

    out << json;
}

std::string StorageFile::ReadJson() const
{
    std::ifstream in;

    in.open(_path, std::ifstream::in);

    if (!in.is_open())
        throw std::filesystem::filesystem_error("Cannot open the storage file.", std::error_code());

    std::stringstream buffer;
    std::string line;
    while (std::getline(in, line))
    {
        buffer << line << '\n';
    }

    in.close();

    std::string content = buffer.str();

    return content;
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