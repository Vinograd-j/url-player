#include "json-music-panel-config.h"

#include <nlohmann/json.hpp>

void JsonMusicPanelConfig::SerializeConfig(const MusicPanelConfig& config) const
{
    nlohmann::json json;

    const Button submitButton = config.GetSubmitButton();

    json["buttons"].push_back(submitButton.ToJson());

    SerializeLayout2d(json, "textPosition", config.GetTextPosition());
    SerializeLayout2d(json, "titleTextBoxPosition", config.GetTitleTextBoxPosition());
    SerializeLayout2d(json, "urlTextBoxPosition", config.GetUrlTextBoxPosition());
    SerializeLayout2d(json, "titleTextBoxSize", config.GetTitleTextBoxSize());
    SerializeLayout2d(json, "urlTextBoxSize", config.GetUrlTextBoxSize());

    json["text"] = { config.GetText() };

    _storage.RewriteJson(json.dump());
}

MusicPanelConfig JsonMusicPanelConfig::DeserializeConfig() const
{
    nlohmann::json json = nlohmann::json::parse(_storage.ReadJson());

    if (json.empty())
        throw std::filesystem::filesystem_error("json doesnt exists or it`s empty", std::error_code());

    Button submitButton = json.contains("buttons") && json["buttons"].is_array()
                      ? Button(json["buttons"][0])
                      : Button();

    std::string text = json.contains("text") && json["text"].is_array() ? json["text"][0].get<std::string>() : "";

    tgui::Layout2d textSize = DeserializeLayout2d(json, "textSize");

    int textLetterSize = json.contains("textLetterSize") && json["textLetterSize"].is_array() ? textLetterSize = json["textLetterSize"][0].get<int>() : 0;

    tgui::Layout2d textPosition = DeserializeLayout2d(json, "textPosition");

    tgui::Layout2d titleTextBoxPosition = DeserializeLayout2d(json, "titleTextBoxPosition");

    tgui::Layout2d titleTextBoxSize = DeserializeLayout2d(json, "titleTextBoxSize");

    tgui::Layout2d urlTextBoxPosition = DeserializeLayout2d(json, "urlTextBoxPosition");

    tgui::Layout2d urlTextBoxSize = DeserializeLayout2d(json, "urlTextBoxSize");

    return MusicPanelConfig(text, textPosition, textSize, textLetterSize, titleTextBoxPosition, titleTextBoxSize, urlTextBoxPosition, urlTextBoxSize, submitButton);
}

void JsonMusicPanelConfig::SerializeLayout2d(nlohmann::json& json, const std::string& key, const tgui::Layout2d& position) const
{
    json[key] = { position.x.getValue(), position.y.getValue() };
}

tgui::Layout2d JsonMusicPanelConfig::DeserializeLayout2d(const nlohmann::json& json, const std::string& key) const
{
    return json.contains(key) && json[key].is_array() ?
           tgui::Layout2d{json[key][0].get<float>(), json[key][1].get<float>()} :
           tgui::Layout2d{};
}
