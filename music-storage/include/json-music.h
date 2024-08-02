#pragma once

#include "music-storage.h"
#include "song.h"
#include "../../storage/json-storage/include/storage-file.h"

class JsonMusic
{

private:

    StorageFile _storage;

public:

    explicit JsonMusic(const std::string& path) : _storage(path) {}

public:

    MusicStorage DesirializeStorage() const;

    void SerializeStorage(const MusicStorage& storage) const;

};
