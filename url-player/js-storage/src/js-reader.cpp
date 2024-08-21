#include "js-reader.h"

#include <filesystem>
#include <fstream>
#include <sstream>

std::wstring JsReader::ReadJsScript(const std::string& scriptName)
{
    std::wifstream file(_pathToScripts + "/" + scriptName);

    if (!file.is_open())
        throw std::filesystem::filesystem_error("File is not founded or cannot be openned", std::error_code());

    std::wstringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}