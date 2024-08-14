#include "music-panel.h"

void MusicPanel::Initialize()
{
    CreateGUI();
    CreateText();
    CreateTextBoxes();
    CreateButton();
}

void MusicPanel::CreateGUI()
{
    _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),"Vinograd URL-PLAYER", sf::Style::Titlebar | sf::Style::Close);
    _gui = std::make_unique<tgui::Gui>(*_window);
}

void MusicPanel::CreateText()
{
    const MusicPanelConfig config = _config.DeserializeConfig();

    _title = tgui::Label::create();

    _title->setText(config.GetText());
    _title->setPosition(config.GetTextPosition());
    _title->setSize(config.GetTextSize());
    _title->getRenderer()->setTextColor(tgui::Color::Black);
    _title->setTextSize(config.GetTextLetterSize());

    _gui->add(_title);
}

void MusicPanel::CreateTextBoxes()
{
    const MusicPanelConfig config = _config.DeserializeConfig();

    _titleInputBox = tgui::EditBox::create();
    _titleInputBox->setPosition(config.GetTitleTextBoxPosition());
    _titleInputBox->setSize(config.GetTitleTextBoxSize());

    _urlInputBox = tgui::EditBox::create();
    _urlInputBox->setPosition(config.GetUrlTextBoxPosition());
    _urlInputBox->setSize(config.GetUrlTextBoxSize());

    _gui->add(_titleInputBox);
    _gui->add(_urlInputBox);

}

void MusicPanel::CreateButton()
{
    const MusicPanelConfig config = _config.DeserializeConfig();

    _submitButton = std::make_unique<Button>(config.GetSubmitButton());
    _submitButton->onPress([this]() { this->OnSumbitButtonClicked(); });

    _submitButton->AddToGui(*_gui);
}

void MusicPanel::OnSumbitButtonClicked()
{
    if (constexpr Validator validator; validator.ValidateTitle(_titleInputBox->getText().toStdString()) && validator.ValidateURL(_urlInputBox->getText().toStdString()))
    {
        auto musicStorage = _musicStorage.DesirializeStorage();
        musicStorage.AddSong(Song(_titleInputBox->getText().toStdString(), _urlInputBox->getText().toStdString()));
        _musicStorage.SerializeStorage(musicStorage);
    }

    Close();
}

void MusicPanel::Open()
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

void MusicPanel::Close()
{
    _onClosed();
    _window->close();
}

bool MusicPanel::Validator::ValidateURL(const std::string& string) const
{
    std::regex youtubeRegex(
        R"(^(?:https?:\/\/)?(?:www\.)?(?:youtube\.com\/(?:[^\/\n\s]+\/\S+\/|(?:v|e(?:mbed)?)\/|\S*?[?&]v=)|youtu\.be\/)([a-zA-Z0-9_-]{11})(?:[?&][^\/\n\s]*)?$)"
    );

    return std::regex_match(string, youtubeRegex);
}

bool MusicPanel::Validator::ValidateTitle(const std::string& string) const
{
    return !string.empty();
}