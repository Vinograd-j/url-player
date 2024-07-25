#pragma once

#include <vector>
#include "button.h"

class UIConfig
{

private:

    std::vector<Button> _buttons;

    tgui::Layout2d _musicListSize;
    tgui::Layout2d _musicListPosition;
    tgui::Layout2d _musicListButtonSize;

public:

    UIConfig(const std::vector<Button>& buttons, const tgui::Layout2d& music_list_size, const tgui::Layout2d& music_list_position,
             const tgui::Layout2d& music_list_button_size):
                                                           _buttons(buttons),
                                                           _musicListSize(music_list_size),
                                                           _musicListPosition(music_list_position),
                                                           _musicListButtonSize(music_list_button_size) {}

    UIConfig() = default;

public:


    const std::vector<Button>& GetButtons() const { return _buttons; }

    const tgui::Layout2d& GetMusicListSize() const { return _musicListSize; }
    const tgui::Layout2d& GetMusicListPosition() const { return _musicListPosition; }
    const tgui::Layout2d& GetMusicListButtonSize() const { return _musicListButtonSize; }

};
