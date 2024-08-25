#include "json-menu-config.h"

#include "button.h"
#include "ui-json-serializer.h"
#include "nlohmann/json.hpp"

void JsonMenuConfig::SerializeConfig(const MenuConfig& config) const
{
    nlohmann::json json;
    const std::vector<Button>& buttons = config.GetButtons();

    for (const auto& button : buttons)
        json["buttons"].push_back(button.ToJson());

    UiJsonSerializer jsonSerilizer;

    jsonSerilizer.SerializeLayout2d(json, "musicListSize", config.GetMusicListSize());
    jsonSerilizer.SerializeLayout2d(json, "musicListPosition", config.GetMusicListPosition());
    jsonSerilizer.SerializeLayout2d(json, "musicListButtonSize", config.GetMusicListButtonSize());

    _storage.RewriteJson(json.dump());
}

MenuConfig JsonMenuConfig::DeserializeConfig() const
{
    nlohmann::json json = nlohmann::json::parse(_storage.ReadJson());

    std::vector<Button> buttons;

    if (!json.empty() && json.contains("buttons") && json["buttons"].is_array())
        for (int i = 0; i < json["buttons"].size(); ++i)
            buttons.push_back(Button(json["buttons"][i]));

    UiJsonSerializer jsonSerializer;

    tgui::Layout2d musicListSize = jsonSerializer.DeserializeLayout2d(json, "musicListSize");

    tgui::Layout2d musicListPosition = jsonSerializer.DeserializeLayout2d(json, "musicListPosition");

    tgui::Layout2d musicListButtonSize = jsonSerializer.DeserializeLayout2d(json, "musicListButtonSize");

    return MenuConfig( buttons, musicListSize, musicListPosition, musicListButtonSize);
}