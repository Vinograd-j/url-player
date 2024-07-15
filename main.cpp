#include <TGUI/TGUI.hpp>
#include "SFML/Graphics/RenderWindow.hpp"
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "SFML/Window/Event.hpp"

sf::Color getRandomColor()
{
    return sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256);
}

int main()
{
    // Инициализация генератора случайных чисел
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(350, 500), "Music List");
    tgui::Gui gui(window);

    // Создание панели с прокруткой
    auto scrollablePanel = tgui::ScrollablePanel::create({"100%", "100%"});
    scrollablePanel->setHorizontalScrollbarPolicy(tgui::Scrollbar::Policy::Never);
    gui.add(scrollablePanel);

    // Добавление песен
    std::vector<std::string> songs = {
        "Song 1", "Song 2", "Song 3", "Song 4", "Song 5",
        "Song 6", "Song 7", "Song 8", "Song 9", "Song 10",
        "Song 6", "Song 7", "Song 8", "Song 9", "Song 10",
        "Song 6", "Song 7", "Song 8", "Song 9", "Song 10",
        "Song 6", "Song 7", "Song 8", "Song 9", "Song 10",
        "Song 6", "Song 7", "Song 8", "Song 9", "Song 10",
        "Song 6", "Song 7", "Song 8", "Song 9", "Song 10",
        "Song 6", "Song 7", "Song 8", "Song 9", "Song 10"
    };

    float songHeight = 30;
    for (size_t i = 0; i < songs.size(); ++i)
    {
        auto songButton = tgui::Button::create(songs[i]);
        songButton->setPosition(0, i * songHeight);
        songButton->setSize({"100%", songHeight});
        songButton->getRenderer()->setBackgroundColor(getRandomColor());
        songButton->getRenderer()->setTextColor(sf::Color::White);
        songButton->setTextSize(18);
       // songButton->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
        scrollablePanel->add(songButton);
    }

    // Устанавливаем размер содержимого панели
    scrollablePanel->setContentSize({350, songs.size() * songHeight});

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            gui.handleEvent(event);
        }

        window.clear();
        gui.draw();
        window.display();
    }

    return 0;
}
