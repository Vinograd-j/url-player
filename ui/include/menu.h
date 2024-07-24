#pragma once

#include <json-music.h>
#include <json-ui-config.h>
#include <memory>
#include "music_list.h"
#include <ui-config.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class Menu
{

private:

    std::unique_ptr<sf::RenderWindow> _window;
    std::unique_ptr<tgui::Gui> _gui;

    JsonUIConfig _config;
    JsonMusic _music;

private:

    const int WINDOW_HEIGHT = 500;
    const int WINDOW_WIDTH = 300;

private:

    std::unique_ptr<MusicList> _musicList {};

    std::unique_ptr<Button> _playButton {};

    std::unique_ptr<Button> _nextButton {};

    std::unique_ptr<Button> _previousButton {};

    std::unique_ptr<Button> _addSongButton {};

public:

    explicit Menu(const JsonMusic& music, const JsonUIConfig& config);

public:

    void AddMusic(const std::string& url);

    void Open();

private:

    void Initialize();
    void InitializeGui();

    void InitializeButtons();
    void LoadSongsList();

    void OnSongChoise();

};
