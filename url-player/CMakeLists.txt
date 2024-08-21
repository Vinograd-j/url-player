add_library(player STATIC
        src/player.cpp
        src/web-view-window.cpp
        src/web-view-browser.cpp
        js-storage/src/js-reader.cpp
)

cmake_policy(SET CMP0135 NEW)

target_include_directories(player PUBLIC include js-storage/include)
