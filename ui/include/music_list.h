#pragma once

#include <TGUI/Widgets/Panel.hpp>
#include <utility>

class MusicList
{

private:

    tgui::Panel _panel;

    tgui::Layout2d _size;

    tgui::Layout2d _position;

    tgui::Layout2d _buttonSize;

public:

    MusicList(tgui::Layout2d size, tgui::Layout2d position, tgui::Layout2d  buttonSize) : _size(std::move(size)), _position(std::move(position)), _buttonSize(std::move(buttonSize)) {}

public:

    void AddButton(const std::string& text, const tgui::Color& color, const std::function<void>& onClick);

private:

    size_t GetButtonsCount() const { return _panel.getWidgets().size(); }

};
