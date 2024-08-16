#pragma once
#include <atomic>
#include <string>

#include <WebView2.h>
#include <wil/com.h>

#include "../../music-storage/include/song.h"

class Player
{

public:

    explicit Player() = default;

private:

     wil::com_ptr<ICoreWebView2Controller> webviewController;
     wil::com_ptr<ICoreWebView2> webviewWindow;
     HWND hWndWebView;

public:

    void Open(const Song& song);
    void Stop();

};
