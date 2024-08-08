#include "confirmation-window.h"

ConfirmationWindow::ConfirmationWindow(const std::string& title, const std::string& text, const std::function<void()>& onYesClicked, const std::function<void()>& onNoClicked) :
                                                                                                                                                                                _title(title),
                                                                                                                                                                                _text(text),
                                                                                                                                                                                _onYesClicked(onYesClicked),
                                                                                                                                                                                _onNoClicked(onNoClicked)
{
    Initialize();
}

void ConfirmationWindow::Initialize()
{
    _messageBox = tgui::MessageBox::create(_title, _text, BUTTONS);

    _messageBox->onButtonPress([this](const tgui::String& buttonText) {
        if (buttonText == BUTTONS[0])
            _onYesClicked();
        else
            _onNoClicked();
    });
}

void ConfirmationWindow::AddToGUI(tgui::Gui& gui)
{
    gui.add(_messageBox);
}

void ConfirmationWindow::RemoveFromGUI(tgui::Gui& gui)
{
    gui.remove(_messageBox);
}