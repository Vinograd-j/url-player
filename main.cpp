#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

void onClick() {
    std::cout << "HELLO@@@!!";
}

bool runExample(tgui::BackendGui& gui)
{

    tgui::Button::Ptr button = tgui::Button::create("123");

    button->setSize(100, 100);

    button->setOrigin(0.5, 0.5);

    button->setPosition(400, 300);

    button->onClick(&onClick);

    gui.add(button);

    return true;
}

int main()
{
    sf::RenderWindow window{ {300, 500}, "TGUI example - SFML_GRAPHICS backend" };

    tgui::Gui gui{window};

    if (runExample(gui))
        gui.mainLoop();
}