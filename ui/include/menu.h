#pragma once

#include <json-music.h>
#include <json-menu-config.h>
#include <memory>
#include <music-panel.h>

#include "music-list.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class Menu
{

private:

    std::unique_ptr<sf::RenderWindow> _window;
    std::unique_ptr<tgui::Gui> _gui;

    JsonMenuConfig _config;
    JsonMusic _music;

    MusicPanel _musicPanel;

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

    explicit Menu(const JsonMusic& music, const JsonMenuConfig& config, const JsonMusicPanelConfig& musicPanelConfigPath) :
                                                                                                                            _config(config),
                                                                                                                            _music(music),
                                                                                                                            _musicPanel(musicPanelConfigPath, music, [this](){ OnMusicPanelClosed(); }) {}

public:

    void OpenMusicPanel();

    void Open();

    void Close();

private:

    void Initialize();
    void CreateGUI();

    void CreateButtons();
    void LoadSongsList();

    void OnMusicPanelClosed();

};
