#pragma once

#include <map>
#include <string>

class Storage
{

private:

    std::map<std::string, std::string> _songs;

public:

    explicit Storage(const std::map<std::string, std::string>& songs) : _songs(songs) {}
    explicit Storage() = default;

public:

    const std::map<std::string, std::string>& GetSongs() const { return _songs; }

};
