#include "../../ui-config/include/json-ui-config.h"

#include "button.h"
#include "../storage/json/json.hpp"

void JsonUIConfig::SerializeConfig(const Config& config)
{
    nlohmann::json json;
    const std::vector<Button>& buttons = config.GetButtons();

    for (const auto& button : buttons)
        json["buttons"].push_back(button.ToJson());

    _storage.RewriteJson(json.dump());
}

Config JsonUIConfig::DeserializeConfig()
{
    nlohmann::json json = nlohmann::json::parse(_storage.ReadJson());

    std::vector<Button> buttons;

    if (!json.empty() && json.contains("buttons"))
        for (int i = 0; i < json["buttons"].size(); ++i)
            buttons.push_back(Button(json["buttons"][i]));

    return Config(buttons);
}
