#pragma once

#include <../../storage/json/json.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/Widgets/Button.hpp>

class Button
{

private:

    tgui::Button::Ptr _button;

    tgui::Layout2d _size;

    tgui::Layout2d _position;

    std::string _text;

public:

    explicit Button(const tgui::Layout2d& size, const tgui::Layout2d& position, const std::string& text);
    explicit Button(const nlohmann::json& json);

public:

    template<typename T>
    void onPress(const std::function<T>& onPress);

    nlohmann::json ToJson() const;

    void AddToGui(tgui::Gui& gui) { gui.add(_button); }

private:

    void Initialize();

};

template<typename T>
void Button::onPress(const std::function<T>& onPress)
{
    _button->onPress(onPress);
}