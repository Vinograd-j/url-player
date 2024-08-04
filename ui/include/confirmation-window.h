#pragma once

#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/Widgets/MessageBox.hpp>

class ConfirmationWindow
{

private:

    tgui::MessageBox::Ptr _messageBox;

    std::string _title;
    std::string _text;

    const int WINDOW_WIDTH = 300;
    const int WINDOW_HEIGHT = 150;

    const std::vector<tgui::String> BUTTONS {"Yes", "No"};

    std::function<void()> _onYesClicked;
    std::function<void()> _onNoClicked;

public:

    explicit ConfirmationWindow(const std::string& title, const std::string& text, const std::function<void()>& onYesClicked, const std::function<void()>& onNoClicked);

public:

    void AddToGUI(tgui::Gui& gui);

    void RemoveFromGUI(tgui::Gui& gui);

private:

    void Initialize();

};
