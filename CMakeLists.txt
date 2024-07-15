cmake_minimum_required(VERSION 3.28)
project(url_player)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR ${SFML_PATH})
find_package(SFML COMPONENTS system window graphics REQUIRED)

set(TGUI_DIR ${TGUI_PATH})
find_package(TGUI REQUIRED)

set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")

add_executable(url_player main.cpp)

target_link_libraries(url_player tgui sfml-system sfml-graphics sfml-window sfml-main)