#include "music_list.h"

#include <TGUI/Widgets/Button.hpp>

void MusicList::AddButton(const std::string& text, const tgui::Color& color, const std::function<void>& onClick)
{

    const tgui::Button::Ptr button = tgui::Button::create(text);

    button->getRenderer()->setBackgroundColor(color);
    button->setSize(_buttonSize);

    constexpr int offset = 100;
    button->setPosition(0, GetButtonsCount() * offset);

    button->onPress(onClick);

    _panel.add(button);
}