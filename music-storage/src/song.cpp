#include "song.h"

nlohmann::json Song::ToJson() const
{
    return nlohmann::json
    {
          {"title", _title},
            {"url", _url}
    };
}
