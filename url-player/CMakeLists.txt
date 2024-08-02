add_library(player STATIC src/player.cpp
        include/player.h)

target_include_directories(player PUBLIC include)

