#pragma once

#include <string>
#include "../../storage/json/json.hpp"

class Song
{

private:

    std::string _title;
	std::string _url;

public:

    explicit Song(const std::string& title, const std::string& url) : _title(title), _url(url) {}

    explicit Song(const nlohmann::json& json) : _title(json.at("title").get<std::string>()), _url(json.at("url").get<std::string>()) {}

public:

    nlohmann::json ToJson() const;

    const std::string& GetTitle() const { return _title; }
    const std::string& GetURL() const { return _url; }

};
