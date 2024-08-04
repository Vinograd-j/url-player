#include "music-list.h"

#include <TGUI/Widgets/Button.hpp>

MusicList::MusicList(const tgui::Layout2d& size, const tgui::Layout2d& position, const tgui::Layout2d& buttonSize)  :
                                                                                                                     _panel(tgui::ScrollablePanel::create(size)),
                                                                                                                     _size(size),
                                                                                                                     _position(std::move(position)),
                                                                                                                     _buttonSize(std::move(buttonSize))
{
    _panel->setPosition(_position);
    _panel->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    _panel->setVerticalScrollbarPolicy(tgui::Scrollbar::Policy::Always);
}

void MusicList::AddButton(const std::string& text, const tgui::Color& color, const std::function<void()>& onLeftClick, const std::function<void()>& onRightClick) const
{
    const tgui::Button::Ptr button = tgui::Button::create(text);

    button->getRenderer()->setBackgroundColor(color);
    button->setSize(_buttonSize);

    constexpr int offset = 40;
    button->setPosition(0, GetButtonsCount() * offset);

    button->onPress(onLeftClick);
    button->onRightClick(onRightClick);

    _panel->add(button);
}

