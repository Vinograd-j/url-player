#include "../include/json-storage.h"
#include "../json/json.hpp"

Storage JsonStorage::DesirializeStorage(const std::string& json) const
{
    const nlohmann::json json = nlohmann::json::parse(json);

    if (json.contains("songs"))
        return Storage(json.at("songs").get<std::map<std::string, std::string>>());

    return Storage();
}

std::string JsonStorage::SerializeStorage(const Storage& storage) const
{
    nlohmann::json json;
    json["songs"] = storage.GetSongs();
    return json.dump();
}