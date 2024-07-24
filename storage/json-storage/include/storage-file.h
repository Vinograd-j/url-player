#pragma once

#include <string>

class StorageFile
{

private:

    std::string _path;

public:

    explicit StorageFile(std::string path);

public:

    void RewriteJson(const std::string& json) const;
    std::string ReadJson() const;

private:

    void InitializeStorage() const;

};