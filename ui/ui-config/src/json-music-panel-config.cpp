#include "json-music-panel-config.h"

#include <nlohmann/json.hpp>

#include "ui-json-serializer.h"

void JsonMusicPanelConfig::SerializeConfig(const MusicPanelConfig& config) const
{
    nlohmann::json json;

    const Button submitButton = config.GetSubmitButton();

    json["buttons"].push_back(submitButton.ToJson());

    UiJsonSerializer jsonSerializer;

    jsonSerializer.SerializeLayout2d(json, "textPosition", config.GetTextPosition());
    jsonSerializer.SerializeLayout2d(json, "titleTextBoxPosition", config.GetTitleTextBoxPosition());
    jsonSerializer.SerializeLayout2d(json, "urlTextBoxPosition", config.GetUrlTextBoxPosition());
    jsonSerializer.SerializeLayout2d(json, "titleTextBoxSize", config.GetTitleTextBoxSize());
    jsonSerializer.SerializeLayout2d(json, "urlTextBoxSize", config.GetUrlTextBoxSize());

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

    UiJsonSerializer jsonSerializer;

    tgui::Layout2d textSize = jsonSerializer.DeserializeLayout2d(json, "textSize");

    int textLetterSize = json.contains("textLetterSize") && json["textLetterSize"].is_array() ? json["textLetterSize"][0].get<int>() : 0;

    tgui::Layout2d textPosition = jsonSerializer.DeserializeLayout2d(json, "textPosition");

    tgui::Layout2d titleTextBoxPosition = jsonSerializer.DeserializeLayout2d(json, "titleTextBoxPosition");

    tgui::Layout2d titleTextBoxSize = jsonSerializer.DeserializeLayout2d(json, "titleTextBoxSize");

    tgui::Layout2d urlTextBoxPosition = jsonSerializer.DeserializeLayout2d(json, "urlTextBoxPosition");

    tgui::Layout2d urlTextBoxSize = jsonSerializer.DeserializeLayout2d(json, "urlTextBoxSize");

    return MusicPanelConfig(text, textPosition, textSize, textLetterSize, titleTextBoxPosition, titleTextBoxSize, urlTextBoxPosition, urlTextBoxSize, submitButton);
}