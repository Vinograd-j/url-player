#include "music-list.h"

#include <thread>
#include <TGUI/Widgets/Button.hpp>

#include "confirmation-window.h"

MusicList::MusicList(const tgui::Layout2d& size, const tgui::Layout2d& position, const tgui::Layout2d& buttonSize, tgui::Gui* gui, JsonMusic* musicStorage, Player* player)  :
                                                                                                                                                             _panel(tgui::ScrollablePanel::create(size)),
                                                                                                                                                             _size(size),
                                                                                                                                                             _position(std::move(position)),
                                                                                                                                                             _buttonSize(std::move(buttonSize)),
                                                                                                                                                             _player(player)
{
    _gui = gui;
    _musicStorage = musicStorage;

    _panel->setPosition(_position);
    _panel->getHorizontalScrollbar()->setPolicy(tgui::Scrollbar::Policy::Never);
    _panel->getVerticalScrollbar()->setPolicy(tgui::Scrollbar::Policy::Always);
}

void MusicList::LoadMusic()
{
    _panel->removeAllWidgets();

    const auto songs = _musicStorage->DesirializeStorage().GetSongs();

    for (const auto& song : songs)
    {
        const tgui::Button::Ptr button = tgui::Button::create(song.GetTitle());

        button->getRenderer()->setBackgroundColor(tgui::Color::White);
        button->setSize(_buttonSize);

        constexpr int offset = 40;
        button->setPosition(0, GetButtonsCount() * offset);

        button->onPress([song, this]{ OnSongChosen(song); });
        button->onRightClick([song, this]{ ShowDeletionDialog(song); });

        _panel->add(button);
    }

}

void MusicList::ShowDeletionDialog(const Song& song)
{
    _confirmationWindow = std::make_unique<ConfirmationWindow>("Delete the song", "Are you sure to delete selected song?", [this, song]
    {
        auto songs = _musicStorage->DesirializeStorage().GetSongs();

        for (int i = 0; i < songs.size(); ++i)
            if (songs[i].ToJson() == song.ToJson())
                songs.erase(songs.begin() + i);

        _musicStorage->SerializeStorage(MusicStorage(songs));
        _confirmationWindow->RemoveFromGUI(*_gui);

        LoadMusic();
    }, [this] { _confirmationWindow->RemoveFromGUI(*_gui); });

    _confirmationWindow->AddToGUI(*_gui);
}

void MusicList::OnSongChosen(const Song& song)
{
    _player->Open(song);
    _lastPlayed = std::make_unique<Song>(song);
}

void MusicList::PlayNext()
{
    auto songs = _musicStorage->DesirializeStorage().GetSongs();
    std::vector<Song>::iterator song = std::find(songs.begin(), songs.end(), *_lastPlayed);

    auto nextSong = song != songs.end() - 1 ? song + 1 : songs.begin();

    OnSongChosen(*nextSong);
}

void MusicList::PlayPrevious()
{
    auto songs = _musicStorage->DesirializeStorage().GetSongs();
    std::vector<Song>::iterator song = std::find(songs.begin(), songs.end(), *_lastPlayed);

    auto previousSong = song != songs.begin() ? song - 1 : songs.end() - 1;

    OnSongChosen(*previousSong);
}