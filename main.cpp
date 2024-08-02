#include "music-storage/include/json-music.h"
#include "ui/include/menu.h"
#include "ui/ui-config/include/json-menu-config.h"

JsonMenuConfig loadConfig()
{
    return JsonMenuConfig("resources/menu-config.json");
}

JsonMusic loadMusic()
{
    return JsonMusic("resources/music.json");
}

JsonMusicPanelConfig loadMusicPanelConfig()
{
    return JsonMusicPanelConfig("resources/music-panel-config.json");
}

int main()
{

    Menu menu(loadMusic(), loadConfig(), loadMusicPanelConfig());
    menu.Open();

}