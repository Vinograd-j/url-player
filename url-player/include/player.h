#pragma once
#include <string>

#include <WebView2.h>
#include <wil/com.h>

class Player
{

public:

    explicit Player() {};

    void Open(const std::wstring url);

    void CreateWebViewInThread(HWND hWndWebView, const std::wstring& url);

private:

     wil::com_ptr<ICoreWebView2Controller> webviewController;
     wil::com_ptr<ICoreWebView2> webviewWindow;
     HWND hWndWebView;

};
