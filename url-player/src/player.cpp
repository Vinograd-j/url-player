#include "player.h"

#include <string>
#include <thread>
#include <Windows.h>
#include <WebView2.h>
#include <wil/com.h>
#include <wrl.h>

void Player::Open(const Song& song) {

    Stop();

    const std::string& url = song.GetURL();

    std::thread webViewThread([&, url]
    {

        hWndWebView = CreateWindowExW(
            0,
            L"STATIC",
            L"WebView Window",
             WS_VISIBLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            400,
            300,
            nullptr,
            nullptr,
            GetModuleHandle(nullptr),
            nullptr
        );

        if (!hWndWebView)
        {
            MessageBox(nullptr, LPCSTR(L"Failed to create WebView window"), LPCSTR(L"Error"), MB_OK);
            return;
        }

        CreateCoreWebView2EnvironmentWithOptions(
            nullptr, nullptr, nullptr,
            Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
                [=](HRESULT result, ICoreWebView2Environment* env) -> HRESULT
                {
                    if (FAILED(result)) return result;

                    env->CreateCoreWebView2Controller(
                        hWndWebView,
                        Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
                            [=](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT
                            {
                                if (FAILED(result)) return result;
                                if (controller != nullptr)
                                {
                                    webviewController = controller;
                                    webviewController->get_CoreWebView2(&webviewWindow);
                                }

                                ICoreWebView2Settings* Settings;
                                webviewWindow->get_Settings(&Settings);
                                Settings->put_IsScriptEnabled(TRUE);
                                Settings->put_AreDefaultScriptDialogsEnabled(TRUE);
                                Settings->put_IsWebMessageEnabled(TRUE);

                                RECT bounds;
                                GetClientRect(hWndWebView, &bounds);
                                webviewController->put_Bounds(bounds);

                                EventRegistrationToken token;

                                webviewWindow->add_NavigationCompleted(
                                    Microsoft::WRL::Callback<ICoreWebView2NavigationCompletedEventHandler>(
                                        [=](ICoreWebView2* sender, ICoreWebView2NavigationCompletedEventArgs* args) -> HRESULT
                                        {
                                            ShowWindow(hWndWebView, SW_SHOWMINIMIZED);

                                            webviewWindow->ExecuteScript(std::wstring(L"document.querySelector('video').play();").c_str(), nullptr);

                                            const std::wstring autoplayJs(L"const toggleButton = document.querySelector('div.ytp-autonav-toggle-button'); if (toggleButton) { toggleButton.click(); }; ");
                                            webviewWindow->ExecuteScript(autoplayJs.c_str(), nullptr);

                                            return S_OK;
                                        }).Get(), &token);

                                webviewWindow->Navigate(std::wstring(url.begin(), url.end()).c_str());

                                return S_OK;
                            })
                            .Get());

                    return S_OK;
                })
                .Get());

        MSG msg;
        while (GetMessage(&msg, nullptr, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        hWndWebView = NULL;
    });

    webViewThread.detach();
}

void Player::Stop()
{
    if (hWndWebView != NULL)
    {
        SendMessage(hWndWebView, WM_CLOSE, 0, 0);
        hWndWebView = NULL;
    }
}