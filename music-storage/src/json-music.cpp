#include "../include/json-music.h"

#include "../../storage/json/json.hpp"

MusicStorage JsonMusic::DesirializeStorage() const
{
    auto json = _storage.ReadJson();

    nlohmann::json j = nlohmann::json::parse(json);

    std::vector<Song> songs;

    if (j.is_object() && j.contains("songs"))
        for (int i = 0; i < j["songs"].size(); ++i)
            songs.push_back(Song(j["songs"][i]));

    return MusicStorage(songs);
}

void JsonMusic::SerializeStorage(const MusicStorage& storage) const
{
    nlohmann::json json;
    json["songs"] = nlohmann::json::array();

    const std::vector<Song>& songs = storage.GetSongs();

    for (const auto& song : songs)
        json["songs"].push_back(song.ToJson());

    _storage.RewriteJson(json.dump());
}