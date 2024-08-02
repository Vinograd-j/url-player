#pragma once

#include "menu-config.h"
#include <string>
#include "storage-file.h"

class JsonMenuConfig
{

private:

    StorageFile _storage;

public:

    explicit JsonMenuConfig(const std::string& path) : _storage(path) {}

public:

    void SerializeConfig(const MenuConfig& config) const;
    MenuConfig DeserializeConfig() const;

};
