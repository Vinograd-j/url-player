#pragma once
#include <complex.h>
#include <string>

class JsReader
{

private:

    std::string _pathToScripts;

public:

    explicit JsReader(const std::string& path) : _pathToScripts(path) {}

public:

    std::wstring ReadJsScript(const std::string& scriptName);

};
