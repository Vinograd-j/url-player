#include <button.h>
#include <TGUI/Layout.hpp>

#include "../../storage/json/json.hpp"

Button::Button(const tgui::Layout2d& size, const tgui::Layout2d& position, const std::string& text) : _size(size), _position(position), _text(text)
{
    Initialize();
}

Button::Button(const nlohmann::json& json) :
                                            _size(tgui::Layout2d(json.at("size").at("width").get<float>(), json.at("size").at("height").get<float>())),
                                            _position(tgui::Layout2d(json.at("position").at("x").get<float>(), json.at("position").at("y").get<float>())),
                                            _text(json.at("text").get<std::string>())
{
    Initialize();
}

void Button::onPress(const std::function<void()>& onPress)
{
    _button->onPress(onPress);
}

nlohmann::json Button::ToJson() const
{
    return nlohmann::json
    {
      {"size", {_size.x.getValue(), _size.y.getValue()}},
        {"position", {_position.x.getValue()}, _position.y.getValue()},
            {"text", _text}
    };
}

void Button::Initialize()
{
    _button = tgui::Button::create();

    _button->setSize(_size);
    _button->setPosition(_position);
    _button->setText(_text);
}