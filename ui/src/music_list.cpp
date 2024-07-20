#include "music_list.h"

#include <TGUI/Widgets/Button.hpp>

MusicList::MusicList(const tgui::Layout2d &size, tgui::Layout2d position, tgui::Layout2d buttonSize)  :
                                                                                                       _panel(tgui::Panel::create(size)),
                                                                                                       _size(size),
                                                                                                       _position(std::move(position)),
                                                                                                       _buttonSize(std::move(buttonSize))
{
    _panel->setOrigin(0.5, 0.5);
}

void MusicList::AddButton(const std::string& text, const tgui::Color& color, const std::function<void>& onClick) const {

    const tgui::Button::Ptr button = tgui::Button::create(text);

    button->getRenderer()->setBackgroundColor(color);
    button->setSize(_buttonSize);

    constexpr int offset = 100;
    button->setPosition(0, GetButtonsCount() * offset);

    button->onPress(onClick);

    _panel->add(button);
}
