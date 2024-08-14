#include "player.h"
#include "windows.h"

void Player::Open(const std::string& url)
{
    // Путь к исполняемому файлу Google Chrome
    const char* chromePath = "C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe";
    // URL, который нужно открыть

    // Команда для запуска нового окна
    std::string command = std::string(chromePath) + " --new-window " + url;

    // Настройки процесса
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Создание процесса
   CreateProcess(
            NULL,               // Не используется
            const_cast<LPSTR>(command.c_str()), // Командная строка
            NULL,               // Атрибуты процесса
            NULL,               // Атрибуты потока
            FALSE,              // Наследование дескрипторов
            0,                  // Создание флагов
            NULL,               // Переменные окружения
            NULL,               // Рабочий каталог
            &si,                // Структура STARTUPINFO
            &pi);                // Структура PROCESS_INFORMATION)

}
