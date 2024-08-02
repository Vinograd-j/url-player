#pragma once

#include "storage-file.h"
#include "music-panel-config.h"

class JsonMusicPanelConfig
{

private:

    StorageFile _storage;

public:

    explicit JsonMusicPanelConfig(const std::string& path) : _storage(path) {}

public:

    void SerializeConfig(const MusicPanelConfig& config) const;

    MusicPanelConfig DeserializeConfig() const;

};