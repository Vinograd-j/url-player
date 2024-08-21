#pragma once

#include <vector>

#include "song.h"

class MusicStorage
{

private:

    std::vector<Song> _songs;

public:

    explicit MusicStorage(const std::vector<Song>& songs) : _songs(songs) {}
    explicit MusicStorage() = default;

    const std::vector<Song>& GetSongs() const { return _songs; }

    void AddSong(const Song& song) { _songs.push_back(song); }

};
