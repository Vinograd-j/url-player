#pragma once

#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/Widgets/ScrollablePanel.hpp>

class MusicList
{

private:

    tgui::ScrollablePanel::Ptr _panel;

private:

    tgui::Layout2d _size;

    tgui::Layout2d _position;

    tgui::Layout2d _buttonSize;

public:

    explicit MusicList(const tgui::Layout2d& size, const tgui::Layout2d& position, const tgui::Layout2d& buttonSize);

public:

    void AddButton(const std::string& text, const tgui::Color& color, const std::function<void()>& onClick) const;

    void AddToGui(tgui::Gui& gui) const { gui.add(_panel); }

private:

    size_t GetButtonsCount() const { return _panel->getWidgets().size(); }

};
