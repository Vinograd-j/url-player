add_library(player STATIC src/player.cpp
        include/player.h)

cmake_policy(SET CMP0135 NEW)

target_link_libraries(player "${webview2_SOURCE_DIR}/build/native/${PLATFORM}/WebView2LoaderStatic.lib")

target_include_directories(player PUBLIC include)

