#include "player.h"

#include <string>
#include <thread>
#include <Windows.h>
#include <WebView2.h>
#include <wil/com.h>
#include <wrl.h>

void Player::Open(const std::wstring url) {
    if (hWndWebView != NULL)
        {
        SendMessage(hWndWebView, WM_CLOSE, 0, 0);
        hWndWebView = NULL;
    }

    std::thread webViewThread([this, url]()
    {

        hWndWebView = CreateWindowExW(
            0,
            L"STATIC",
            L"WebView Window",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            800,
            600,
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

                                webviewWindow->Navigate(url.c_str());

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
