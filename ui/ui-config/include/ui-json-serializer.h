#pragma once
#include <nlohmann/json.hpp>
#include <TGUI/Layout.hpp>

class UiJsonSerializer
{

public:

    explicit UiJsonSerializer() = default;

public:

    void SerializeLayout2d(nlohmann::json& json, const std::string& key, const tgui::Layout2d& position) const;

    tgui::Layout2d DeserializeLayout2d(const nlohmann::json& json, const std::string& key) const;

};
