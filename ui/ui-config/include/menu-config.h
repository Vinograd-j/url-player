#pragma once

#include <vector>
#include "button.h"

class MenuConfig
{

private:

    std::vector<Button> _buttons;

    tgui::Layout2d _musicListSize;
    tgui::Layout2d _musicListPosition;
    tgui::Layout2d _musicListButtonSize;

public:

    MenuConfig(const std::vector<Button>& buttons, const tgui::Layout2d& music_list_size, const tgui::Layout2d& music_list_position,
             const tgui::Layout2d& music_list_button_size):
                                                           _buttons(buttons),
                                                           _musicListSize(music_list_size),
                                                           _musicListPosition(music_list_position),
                                                           _musicListButtonSize(music_list_button_size) {}

    MenuConfig() = default;

public:


    const std::vector<Button>& GetButtons() const { return _buttons; }

    const tgui::Layout2d& GetMusicListSize() const { return _musicListSize; }
    const tgui::Layout2d& GetMusicListPosition() const { return _musicListPosition; }
    const tgui::Layout2d& GetMusicListButtonSize() const { return _musicListButtonSize; }

};
