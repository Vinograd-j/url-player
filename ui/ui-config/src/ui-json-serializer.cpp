#include "../include/ui-json-serializer.h"

void UiJsonSerializer::SerializeLayout2d(nlohmann::json& json, const std::string& key, const tgui::Layout2d& position) const
{
    json[key] = { position.x.getValue(), position.y.getValue() };
}

tgui::Layout2d UiJsonSerializer::DeserializeLayout2d(const nlohmann::json& json, const std::string& key) const
{
    return json.contains(key) && json[key].is_array() ?
           tgui::Layout2d{json[key][0].get<float>(), json[key][1].get<float>()} :
           tgui::Layout2d{};
}
