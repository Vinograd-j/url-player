#pragma once

#include "button.h"
#include <TGUI/Layout.hpp>

class MusicPanelConfig {

private:

    std::string _text;
    tgui::Layout2d _textPosition;
    tgui::Layout2d _textSize;
    int _textLetterSize;

    tgui::Layout2d _titleBoxPosition;
    tgui::Layout2d _titleBoxSize;

    tgui::Layout2d _urlBoxPosition;
    tgui::Layout2d _urlBoxSize;

    Button _submitButton;

public:
    MusicPanelConfig(const std::string& text, const tgui::Layout2d& textPosition, const tgui::Layout2d& textSize, int textLetterSize, const tgui::Layout2d& titleTextBoxPosition,
                        const tgui::Layout2d& titleTextBoxSize, const tgui::Layout2d& urlTextBoxPosition, const tgui::Layout2d& urlTextBoxSize, const Button& submitButton)
                                                                                                                                                                       : _text(text),
                                                                                                                                                                         _textPosition(textPosition),
                                                                                                                                                                         _textSize(textSize),
                                                                                                                                                                         _textLetterSize(textLetterSize),
                                                                                                                                                                         _titleBoxPosition(titleTextBoxPosition),
                                                                                                                                                                         _titleBoxSize(titleTextBoxSize),
                                                                                                                                                                         _urlBoxPosition(urlTextBoxPosition),
                                                                                                                                                                         _urlBoxSize(urlTextBoxSize),
                                                                                                                                                                         _submitButton(submitButton) {}

public:

    const std::string& GetText() const { return _text; }

    const tgui::Layout2d& GetTextPosition() const { return _textPosition; }

    const tgui::Layout2d& GetTextSize() const { return _textSize; }

    int GetTextLetterSize() const { return _textLetterSize; }

    const tgui::Layout2d& GetTitleTextBoxPosition() const { return _titleBoxPosition; }

    const tgui::Layout2d& GetTitleTextBoxSize() const { return _titleBoxSize; }

    const tgui::Layout2d& GetUrlTextBoxPosition() const { return _urlBoxPosition; }

    const tgui::Layout2d& GetUrlTextBoxSize() const { return _urlBoxSize; }

    const Button& GetSubmitButton() const { return _submitButton; }

};