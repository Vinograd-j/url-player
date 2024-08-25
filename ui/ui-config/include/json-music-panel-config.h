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

private:

    void SerializeLayout2d(nlohmann::json& json, const std::string& key, const tgui::Layout2d& position) const;

    tgui::Layout2d DeserializeLayout2d(const nlohmann::json& json, const std::string& key) const;

};