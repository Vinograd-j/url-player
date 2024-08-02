#include "menu.h"

void Menu::Initialize()
{
    CreateGUI();
    CreateButtons();
    LoadSongsList();
}

void Menu::CreateGUI()
{
    _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Vinograd URL-PLAYER", sf::Style::Titlebar | sf::Style::Close);
    _gui = std::make_unique<tgui::Gui>(*_window);
}

void Menu::CreateButtons()
{
    auto buttons = _config.DeserializeConfig().GetButtons();

    _playButton = std::make_unique<Button>(buttons[0]);
    _nextButton = std::make_unique<Button>(buttons[1]);
    _previousButton = std::make_unique<Button>(buttons[2]);
    _addSongButton = std::make_unique<Button>(buttons[3]);

    _playButton->AddToGui(*_gui);
    _nextButton->AddToGui(*_gui);
    _previousButton->AddToGui(*_gui);
    _addSongButton->AddToGui(*_gui);

    _addSongButton->onPress([this]() { OpenMusicPanel(); });
}

void Menu::LoadSongsList()
{

    MenuConfig config = _config.DeserializeConfig();

    _musicList = std::make_unique<MusicList>(config.GetMusicListSize(), config.GetMusicListPosition(), config.GetMusicListButtonSize());

    auto musicStorage = _music.DesirializeStorage();

    for (const auto& song : musicStorage.GetSongs())
        _musicList->AddButton(song.GetTitle(), tgui::Color::White, [this]() { Menu::OnSongChoise(); });

    _musicList->AddToGui(*_gui);
}

void Menu::OnMusicPanelClosed()
{
    LoadSongsList();
}

void Menu::OpenMusicPanel()
{
    _musicPanel.Open();
}

void Menu::OnSongChoise()
{
}

void Menu::Open()
{
    Initialize();

    sf::Event event;
    while (_window->isOpen())
    {
        while (_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Close();

            _gui->handleEvent(event);
        }

        if (_window->hasFocus())
        {
            _window->clear({240, 240, 240});
            _gui->draw();
            _window->display();
        }

    }

}

void Menu::Close()
{
    _window->close();
}
