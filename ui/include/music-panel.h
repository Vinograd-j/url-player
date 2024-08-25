#pragma once

#include <button.h>
#include <json-music-panel-config.h>
#include <json-music.h>
#include <TGUI/TGUI.hpp>

class MusicPanel
{

private:

    JsonMusicPanelConfig _config;
    JsonMusic _musicStorage;

    std::function<void()> _onClosed;

private:

    std::unique_ptr<sf::RenderWindow> _window;
    std::unique_ptr<tgui::Gui> _gui ;

    tgui::Label::Ptr _title;

    tgui::EditBox::Ptr _titleInputBox;
    tgui::EditBox::Ptr _urlInputBox;

    std::unique_ptr<Button> _submitButton;

private:

    const int WINDOW_HEIGHT = 250;
    const int WINDOW_WIDTH = 500;

private:

    void OnSumbitButtonClicked();

public:

    explicit MusicPanel(const JsonMusicPanelConfig& config, const JsonMusic& musicStoragePath, const std::function<void()>& onClosed = std::function<void()>()) : _config(config),
                                                                                                                                                                  _musicStorage(musicStoragePath),
                                                                                                                                                                  _onClosed(onClosed) {}

    void Initialize();

    void CreateGUI();
    void CreateText();
    void CreateTextBoxes();
    void CreateButton();

public:

    void Open();

    void Close();

private:

    class Validator
    {

    public:

        bool ValidateURL(const std::string& string) const;

        bool ValidateTitle(const std::string& string) const;

        bool IsExists(const std::vector<Song>& songs, const Song& song) const;

    };

};