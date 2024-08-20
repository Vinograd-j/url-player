#include "player.h"

#include <string>
#include <thread>
#include <Windows.h>
#include <WebView2.h>
#include <wil/com.h>
#include <wrl.h>

Player::Player()
{
    Init();
}

void Player::Open(const Song& song)
{
    auto url = song.GetURL();

    webviewWindow->Navigate(std::wstring(url.begin(), url.end()).c_str());
}

void Player::Init()
{
    hWndWebView = CreateWindowExW(
        0,
        L"STATIC",
        L"URL-PLAYER WEB",
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

    if (!hWndWebView) {
        MessageBox(nullptr, LPCSTR(L"Failed to create URL-PLAYER WEB window"), LPCSTR(L"Error"), MB_OK);
        return;
    }

    HRESULT hr = CreateCoreWebView2EnvironmentWithOptions(
        nullptr, nullptr, nullptr,
        Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
            [this](HRESULT result, ICoreWebView2Environment* env) -> HRESULT
            {
                if (FAILED(result))
                    return result;

                return env->CreateCoreWebView2Controller(
                    hWndWebView,
                    Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
                        [this](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {
                            if (FAILED(result))
                                return result;

                            if (controller != nullptr) {
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
                                    [this](ICoreWebView2* sender, ICoreWebView2NavigationCompletedEventArgs* args) -> HRESULT
                                    {
                                        const std::wstring autoplayJs(L"const toggleButton = document.querySelector('div.ytp-autonav-toggle-button'); if (toggleButton) { toggleButton.click(); }; ");
                                        webviewWindow->ExecuteScript(autoplayJs.c_str(), nullptr);

                                        webviewWindow->ExecuteScript(std::wstring(L"document.querySelector('video').play();").c_str(), nullptr);

                                        return S_OK;
                                    }
                                ).Get(), &token);

                            ShowWindow(hWndWebView, SW_SHOWMINIMIZED);

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

void Player::Stop()
{
    if (hWndWebView != NULL && webviewWindow != nullptr && webviewController != nullptr) {
        webviewWindow->Stop();
        ShowWindow(hWndWebView, SW_SHOWMINIMIZED);
        webviewWindow->Navigate(L"about:blank");
    }
}