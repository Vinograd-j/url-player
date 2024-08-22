#include "web-view-browser.h"

#include <iostream>
#include <wrl/event.h>

#include "../js-storage/include/js-reader.h"

WebViewBrowser::WebViewBrowser(const std::string& pathToScripts) : _jsReader(pathToScripts)
{
    Initialize();
}

void WebViewBrowser::Initialize()
{
    _window = std::make_unique<WebViewWindow>(L"URL-PLAYER WEB", L"WebView", WS_VISIBLE, WINDOW_HEIGHT, WINDOW_WIDTH);

        HRESULT hr = CreateCoreWebView2EnvironmentWithOptions(
        nullptr, nullptr, nullptr,
        Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
            [this](HRESULT result, ICoreWebView2Environment* env) -> HRESULT
            {
                if (FAILED(result))
                    return result;

                return env->CreateCoreWebView2Controller(
                    _window->GetWindowHWND(),
                    Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
                        [this](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {
                            if (FAILED(result))
                                return result;

                            if (controller != nullptr) {
                                _webViewController = controller;
                                _webViewController->get_CoreWebView2(&_webViewWindow);
                            }

                            ICoreWebView2Settings* Settings;
                            _webViewWindow->get_Settings(&Settings);
                            Settings->put_IsScriptEnabled(TRUE);
                            Settings->put_AreDefaultScriptDialogsEnabled(TRUE);
                            Settings->put_IsWebMessageEnabled(TRUE);

                            RECT bounds;
                            GetClientRect(_window->GetWindowHWND(), &bounds);
                            _webViewController->put_Bounds(bounds);

                            EventRegistrationToken token;
                            _webViewWindow->add_NavigationCompleted(
                                Microsoft::WRL::Callback<ICoreWebView2NavigationCompletedEventHandler>(
                                [this](ICoreWebView2* sender, ICoreWebView2NavigationCompletedEventArgs* args) -> HRESULT
                                {
                                    return OnNavigationCompleted(sender, args);
                                }
                                ).Get(), &token);

                            ShowWindow(_window->GetWindowHWND(), SW_SHOWMINIMIZED);

                            return S_OK;
                        }
                    ).Get()
                );
            }
        ).Get());

    if (FAILED(hr)) {
        MessageBox(nullptr, LPCSTR(L"Failed to create WebView2 environment"), LPCSTR(L"Error"), MB_OK);
        return;
    }
}

HRESULT WebViewBrowser::OnNavigationCompleted(ICoreWebView2* sender, ICoreWebView2NavigationCompletedEventArgs* args)
{

    BOOL isSuccess;
    args->get_IsSuccess(&isSuccess);

    if (isSuccess)
    {
        const std::wstring autoplayJs = _jsReader.ReadJsScript("autoplay.js");
        _webViewWindow->ExecuteScript(autoplayJs.c_str(), nullptr);

        const std::wstring checkVideoLoadedJs = _jsReader.ReadJsScript("starter.js");

        HRESULT execute_script = _webViewWindow->ExecuteScript(checkVideoLoadedJs.c_str(), nullptr);

        std::cout << execute_script;
    }

    return S_OK;
}

void WebViewBrowser::Open(const std::string& url)
{
    _webViewWindow->Navigate(std::wstring(url.begin(), url.end()).c_str());
}

void WebViewBrowser::Stop()
{
    if (_window->GetWindowHWND() != NULL && _webViewWindow != nullptr && _webViewController != nullptr) {
        _webViewWindow->Stop();
        ShowWindow(_window->GetWindowHWND(), SW_SHOWMINIMIZED);
        _webViewWindow->Navigate(L"about:blank");
    }
}
