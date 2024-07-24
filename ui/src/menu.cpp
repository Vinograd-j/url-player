#include "menu.h"

Menu::Menu(const JsonMusic& music, const JsonUIConfig& config) :  _config(config), _music(music)
{
    Initialize();
}

void Menu::Initialize()
{
    InitializeGui();
    InitializeButtons();
    LoadSongsList();
}

void Menu::InitializeGui()
{
    _window =  std::make_unique<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Vinograd URL-PLAYER", sf::Style::Titlebar | sf::Style::Close);
    _gui = std::make_unique<tgui::Gui>(*_window);
}

void Menu::InitializeButtons()
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
}

void Menu::LoadSongsList()
{
    const tgui::Layout2d MUSIC_LIST_SIZE(WINDOW_WIDTH / 1.5, WINDOW_HEIGHT / 1.5);
    const tgui::Layout2d MUSIC_LIST_POSITION( (WINDOW_WIDTH - WINDOW_WIDTH / 1.5) / 2, (WINDOW_HEIGHT - WINDOW_HEIGHT / 1.5) / 2);
    const tgui::Layout2d MUSIC_LIST_BUTTON_SIZE( 300 / 1.8, 30);

    _musicList = std::make_unique<MusicList>(MUSIC_LIST_SIZE, MUSIC_LIST_POSITION, MUSIC_LIST_BUTTON_SIZE);

    auto desirialize_storage = _music.DesirializeStorage();

    for (const auto& song : desirialize_storage.GetSongs())
        _musicList->AddButton(song.GetTitle(), tgui::Color::White, [this]() { Menu::OnSongChoise(); });

    _musicList->AddToGui(*_gui);
}

void Menu::OnSongChoise()
{
}

void Menu::Open()
{
    _gui->mainLoop();
}