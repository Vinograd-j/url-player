#pragma once
#include <atomic>
#include <condition_variable>
#include <string>

#include <WebView2.h>
#include <wil/com.h>

#include "../../music-storage/include/song.h"

class Player
{

private:

     wil::com_ptr<ICoreWebView2Controller> webviewController;
     wil::com_ptr<ICoreWebView2> webviewWindow;
     HWND hWndWebView;

public:

    void Open(const Song& song);
    void Stop();

};
