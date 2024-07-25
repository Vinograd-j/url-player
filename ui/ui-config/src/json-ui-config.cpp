#include "../../ui-config/include/json-ui-config.h"

#include "button.h"
#include "../storage/json/json.hpp"

void JsonUIConfig::SerializeConfig(const Config& config)
{
    nlohmann::json json;
    const std::vector<Button>& buttons = config.GetButtons();

    for (const auto& button : buttons)
        json["buttons"].push_back(button.ToJson());

    json["musicListSize"] = { config.GetMusicListSize().x.getValue(), config.GetMusicListSize().y.getValue() };
    json["musicListPosition"] = { config.GetMusicListPosition().x.getValue(), config.GetMusicListPosition().y.getValue() };
    json["musicListButtonSize"] = { config.GetMusicListButtonSize().x.getValue(), config.GetMusicListButtonSize().y.getValue() };

    _storage.RewriteJson(json.dump());
}

Config JsonUIConfig::DeserializeConfig()
{
    nlohmann::json json = nlohmann::json::parse(_storage.ReadJson());

    std::vector<Button> buttons;

    tgui::Layout2d musicListSize;
    tgui::Layout2d musicListPosition;
    tgui::Layout2d musicListButtonSize;

    if (!json.empty() && json.contains("buttons") && json["buttons"].is_array())
        for (int i = 0; i < json["buttons"].size(); ++i)
            buttons.push_back(Button(json["buttons"][i]));

    if (json.contains("musicListSize") && json["musicListSize"].is_array())
        musicListSize = tgui::Layout2d{ json["musicListSize"][0].get<float>(), json["musicListSize"][1].get<float>() };

    if (json.contains("musicListPosition") && json["musicListPosition"].is_array())
        musicListPosition = tgui::Layout2d{ json["musicListPosition"][0].get<float>(), json["musicListPosition"][1].get<float>() };

    if (json.contains("musicListButtonSize") && json["musicListButtonSize"].is_array())
        musicListButtonSize = tgui::Layout2d{ json["musicListButtonSize"][0].get<float>(), json["musicListButtonSize"][1].get<float>() };

    return Config(buttons, musicListSize, musicListPosition, musicListButtonSize);
}
