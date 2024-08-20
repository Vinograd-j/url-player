#pragma once

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

    explicit Player();;

public:

    void Open(const Song& song);

    void Init();

    void Loop();

    void Stop();

private:
    
     HRESULT OnEnvironmentCreated(HRESULT result, ICoreWebView2Environment* env, const std::string& url);

     HRESULT OnControllerCreated(HRESULT result, ICoreWebView2Controller* controller, const std::string& url);

     HRESULT OnNavigationCompleted(ICoreWebView2* sender, ICoreWebView2NavigationCompletedEventArgs* args);


};
