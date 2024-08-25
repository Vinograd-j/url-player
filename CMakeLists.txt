cmake_minimum_required(VERSION 3.28)
project(url_player)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")

#set(CMAKE_VERBOSE_MAKEFILE ON)

include(FetchContent)

set(TGUI_BACKEND SFML_GRAPHICS)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
)

FetchContent_Declare(
        TGUI
        GIT_REPOSITORY https://github.com/texus/TGUI.git
        GIT_TAG 1.x
)

FetchContent_Declare(
        wil
        URL https://www.nuget.org/api/v2/package/Microsoft.Windows.ImplementationLibrary/1.0.211019.2
        URL_HASH SHA1=FB082B22DC30C11CCDB118A0EB9B8A32E99765B1
)

FetchContent_Declare(
        webview2
        URL https://www.nuget.org/api/v2/package/Microsoft.Web.WebView2/1.0.1072.54
        URL_HASH SHA1=aa8ae9db5015a9184011bb195efc5c8caa58a86b
)

FetchContent_Declare(json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)

FetchContent_MakeAvailable(SFML TGUI wil webview2 json)

include_directories(${json_SOURCE_DIR}/include)
include_directories(SYSTEM "${wil_SOURCE_DIR}/include/")
include_directories(SYSTEM "${webview2_SOURCE_DIR}/build/native/include/")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(PLATFORM "x64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(PLATFORM "x86")
endif()

link_libraries("${webview2_SOURCE_DIR}/build/native/${PLATFORM}/WebView2LoaderStatic.lib")

add_executable(url_player WIN32 main.cpp)

add_subdirectory(url-player)
add_subdirectory(storage)
add_subdirectory(music-storage)
add_subdirectory(ui)

target_link_libraries(url_player PRIVATE tgui ui json-storage music-storage)

set_target_properties(url_player PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/url-player/bin)

set_target_properties(json-storage PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/url-player/storage)
set_target_properties(music-storage PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/url-player/music-storage)
set_target_properties(ui PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/url-player/ui)

add_custom_command(TARGET url_player POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${CMAKE_BINARY_DIR}/url-player/bin/resources
)

add_custom_command(TARGET url_player POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        ${CMAKE_BINARY_DIR}/url-player/bin/resources
)