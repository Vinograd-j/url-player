#include "song.h"

bool Song::operator==(const Song& other) const
{
    return _title == other._title && _url == other._url;
}

nlohmann::json Song::ToJson() const
{
    return nlohmann::json
    {
          {"title", _title},
            {"url", _url}
    };
}
