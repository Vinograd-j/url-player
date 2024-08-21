#include "player.h"

#include <string>


void Player::Open(const Song& song)
{
    auto url = song.GetURL();

    _browser.Open(url);
}

void Player::Stop()
{
    _browser.Stop();
}