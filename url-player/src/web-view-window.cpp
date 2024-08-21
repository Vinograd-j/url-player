#include "web-view-window.h"

WebViewWindow::WebViewWindow(const std::wstring& windowName, const std::wstring& className, LONG windowStyle, int height, int width) :
                                                                                                                                        _windowName(windowName),
                                                                                                                                        _className(className),
                                                                                                                                        _windowStyle(windowStyle),
                                                                                                                                        _height(height),
                                                                                                                                        _width(width)
{
    Initialize();
}

void WebViewWindow::Initialize()
{
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = _className.c_str();

    RegisterClassW(&wc);

    _hwndWindow = CreateWindowExW(
        0,
        _className.c_str(),
        _windowName.c_str(),
        _windowStyle,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        _width,
        _height,
        nullptr,
        nullptr,
        GetModuleHandle(nullptr),
        nullptr
    );

    if (!_hwndWindow)
        MessageBox(nullptr, LPCSTR(L"Failed to create URL-PLAYER WEB window"), LPCSTR(L"Error"), MB_OK);
}

LRESULT WebViewWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
        case WM_CLOSE:
                return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
        return 0;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}
