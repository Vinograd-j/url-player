#pragma once

#include <string>

#include "windows.h"

class WebViewWindow
{

private:

    HWND _hwndWindow;

    std::wstring _windowName;
    std::wstring _className;

    LONG _windowStyle;

    int _height;
    int _width;

public:

    explicit WebViewWindow(const std::wstring& windowName, const std::wstring& className, LONG windowStyle, int height, int width);

public:

    void Initialize();

    HWND GetWindowHWND() const { return _hwndWindow; }

private:

    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

};
