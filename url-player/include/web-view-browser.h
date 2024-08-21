#pragma once
#include <intsafe.h>
#include <memory>
#include <string>
#include <WebView2.h>
#include <wil/com.h>

#include "../js-storage/include/js-reader.h"
#include "web-view-window.h"

class WebViewBrowser
{

private:

    wil::com_ptr<ICoreWebView2> _webViewWindow;
    wil::com_ptr<ICoreWebView2Controller> _webViewController;

    std::unique_ptr<WebViewWindow> _window;

    const int WINDOW_WIDTH = 400;
    const int WINDOW_HEIGHT = 300;

    JsReader _jsReader;

public:

    explicit WebViewBrowser(const std::string& pathToScripts);

public:

    void Open(const std::string& url);

    void Stop();

private:

    void Initialize();

    HRESULT OnNavigationCompleted(ICoreWebView2* sender, ICoreWebView2NavigationCompletedEventArgs* args);

};
