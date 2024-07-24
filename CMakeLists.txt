cmake_minimum_required(VERSION 3.28)
project(url_player)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")

#set(CMAKE_VERBOSE_MAKEFILE ON)

set(SFML_DIR ${SFML_PATH})
find_package(SFML COMPONENTS system window graphics REQUIRED PATHS ${SFML_DIR})

set(TGUI_DIR ${TGUI_PATH})
find_package(TGUI REQUIRED PATHS ${TGUI_DIR})

set(TGUI_INCLUDE_DIR C:/libs/TGUI/include)
set(SFML_INCLUDE_DIR C:/libs/SFML/include)

add_executable(url_player WIN32 main.cpp)

add_subdirectory(storage)
add_subdirectory(music-storage)
add_subdirectory(ui)

target_link_libraries(url_player PRIVATE ui json-storage music-storage)

# Указываем, что выводимые файлы будут в папке bin
set_target_properties(url_player PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/url-player/bin)

# Создание папок для статических библиотек
set_target_properties(json-storage PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/url-player/storage)
set_target_properties(music-storage PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/url-player/music-storage)
set_target_properties(ui PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/url-player/ui)

# Создание папки resources и копирование туда файлов
add_custom_command(TARGET url_player POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${CMAKE_BINARY_DIR}/url-player/bin/resources
)

add_custom_command(TARGET url_player POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        ${CMAKE_BINARY_DIR}/url-player/bin/resources
)