#pragma once

#include <json-music.h>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/Widgets/ScrollablePanel.hpp>

#include "confirmation-window.h"

class MusicList
{

private:

    tgui::ScrollablePanel::Ptr _panel;

    tgui::Gui* _gui;

    std::unique_ptr<ConfirmationWindow> _confirmationWindow;

private:

    JsonMusic* _musicStorage;

private:

    tgui::Layout2d _size;

    tgui::Layout2d _position;

    tgui::Layout2d _buttonSize;

public:

    explicit MusicList(const tgui::Layout2d& size, const tgui::Layout2d& position, const tgui::Layout2d& buttonSize, tgui::Gui* gui, JsonMusic* musicStorage);

public:

    void LoadMusic();

    void AddToGui(tgui::Gui& gui) const { gui.add(_panel); }

    void ShowDeletionDialog(const Song& song);
    void OnSongChosen(const Song& song);

private:

    size_t GetButtonsCount() const { return _panel->getWidgets().size(); }

};
