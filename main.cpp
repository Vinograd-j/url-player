#include <filesystem>

#include "music-storage/include/json-music.h"
#include "ui/include/menu.h"
#include "ui/ui-config/include/json-ui-config.h"

JsonUIConfig loadConfig()
{
    return JsonUIConfig("resources/ui-config.json");
}

JsonMusic loadMusic()
{
    return JsonMusic("resources/music.json");
}

int main()
{

    Menu menu(loadMusic(), loadConfig());
    menu.Open();

}