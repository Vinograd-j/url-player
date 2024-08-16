add_library(player STATIC src/player.cpp
        include/player.h)

cmake_policy(SET CMP0135 NEW)

target_include_directories(player PUBLIC include)

