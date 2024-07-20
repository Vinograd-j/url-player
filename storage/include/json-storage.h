#pragma once

#include "storage.h"

class JsonStorage
{

public:

    Storage DesirializeStorage(const std::string& json) const;

    std::string SerializeStorage(const Storage& storage) const;

};
