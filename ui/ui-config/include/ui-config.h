#pragma once

#include <vector>
#include "button.h"

class Config
{

private:

    std::vector<Button> _buttons;

public:

    Config() = default;
    explicit Config(const std::vector<Button>& buttons) : _buttons(buttons) {}

public:

    const std::vector<Button>& GetButtons() const { return _buttons; }

};
