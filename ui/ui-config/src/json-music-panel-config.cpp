#include "json-music-panel-config.h"

#include <nlohmann/json.hpp>

void JsonMusicPanelConfig::SerializeConfig(const MusicPanelConfig& config) const
{
    nlohmann::json json;

    const Button submitButton = config.GetSubmitButton();

    json["buttons"].push_back(submitButton.ToJson());
    json["textPosition"] = { config.GetTextPosition().x.getValue(), config.GetTextPosition().y.getValue() };
    json["text"] = { config.GetText() };
    json["titleTextBoxPosition"] = { config.GetTitleTextBoxPosition().x.getValue(), config.GetTitleTextBoxPosition().y.getValue() };
    json["titleTextBoxSize"] = { config.GetTitleTextBoxSize().x.getValue(), config.GetTitleTextBoxSize().y.getValue() };
    json["urlTextBoxPosition"] = { config.GetUrlTextBoxPosition().x.getValue(), config.GetUrlTextBoxPosition().y.getValue() };
    json["urlTextBoxSize"] = { config.GetUrlTextBoxSize().x.getValue(), config.GetUrlTextBoxSize().y.getValue() };

    _storage.RewriteJson(json.dump());
}

MusicPanelConfig JsonMusicPanelConfig::DeserializeConfig() const
{
    nlohmann::json json = nlohmann::json::parse(_storage.ReadJson());

    std::string text;
    tgui::Layout2d textPosition;
    tgui::Layout2d textSize;
    int textLetterSize;

    tgui::Layout2d titleBoxPosition;
    tgui::Layout2d titleBoxSize;

    tgui::Layout2d urlBoxPosition;
    tgui::Layout2d urlBoxSize;

    Button submitButton;

    if (json.empty())
        throw std::filesystem::filesystem_error("json doesnt exists or it`s empty", std::error_code());

    if (json.contains("buttons") && json["buttons"].is_array())
        submitButton = Button(json["buttons"][0]);

    if (json.contains("text") && json["text"].is_array())
        text = json["text"][0].get<std::string>();

    if (json.contains("textSize") && json["textSize"].is_array())
        textSize = tgui::Layout2d{json["textSize"][0].get<float>(), json["textSize"][1].get<float>() };

    if (json.contains("textLetterSize") && json["textLetterSize"].is_array())
        textLetterSize = json["textLetterSize"][0].get<int>();

    if (json.contains("textPosition") && json["textPosition"].is_array())
        textPosition = tgui::Layout2d{ json["textPosition"][0].get<float>(), json["textPosition"][1].get<float>() };

    if (json.contains("titleTextBoxPosition") && json["titleTextBoxPosition"].is_array())
        titleBoxPosition = tgui::Layout2d{ json["titleTextBoxPosition"][0].get<float>(), json["titleTextBoxPosition"][1].get<float>() };

    if (json.contains("titleTextBoxSize") && json["titleTextBoxSize"].is_array())
        titleBoxSize = tgui::Layout2d{ json["titleTextBoxSize"][0].get<float>(), json["titleTextBoxSize"][1].get<float>() };

    if (json.contains("urlTextBoxPosition") && json["urlTextBoxPosition"].is_array())
        urlBoxPosition = tgui::Layout2d{ json["urlTextBoxPosition"][0].get<float>(), json["urlTextBoxPosition"][1].get<float>() };

    if (json.contains("urlTextBoxSize") && json["urlTextBoxSize"].is_array())
        urlBoxSize = tgui::Layout2d{ json["urlTextBoxSize"][0].get<float>(), json["urlTextBoxSize"][1].get<float>() };

    return MusicPanelConfig(text, textPosition, textSize, textLetterSize, titleBoxPosition, titleBoxSize, urlBoxPosition, urlBoxSize, submitButton);
}