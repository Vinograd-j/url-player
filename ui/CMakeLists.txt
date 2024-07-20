add_library(ui STATIC
        src/music_list.cpp
        src/music_list.cpp
        src/menu.cpp
        include/menu.h
)
target_include_directories(ui PRIVATE include)

target_link_libraries(ui PRIVATE tgui sfml-system sfml-graphics sfml-window sfml-main)