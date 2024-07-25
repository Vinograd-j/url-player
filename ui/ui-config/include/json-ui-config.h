#pragma once

#include "ui-config.h"
#include <string>
#include "storage-file.h"

class JsonUIConfig
{

private:

    StorageFile _storage;

public:

    explicit JsonUIConfig(const std::string& path) : _storage(path) {}

public:

    void SerializeConfig(const UIConfig& config);
    UIConfig DeserializeConfig();

};
