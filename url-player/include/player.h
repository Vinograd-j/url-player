#pragma once

#include "web-view-browser.h"
#include "../../music-storage/include/song.h"

class Player
{

private:

    WebViewBrowser _browser;

public:

    explicit Player() : _browser("resources/scripts") {}

public:

    void Open(const Song& song);

    void Stop();

};
