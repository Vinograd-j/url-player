add_library(ui STATIC
        src/music_list.cpp
        src/button.cpp
        ui-config/src/json-ui-config.cpp
        src/menu.cpp
)

message(TGUI_INCLUDE_DIR:  ${TGUI_INCLUDE_DIR})

target_include_directories(ui PUBLIC ${TGUI_INCLUDE_DIR} ${SFML_INCLUDE_DIR} include ${CMAKE_SOURCE_DIR}/json ui-config/include)

target_link_libraries(ui PRIVATE tgui sfml-system sfml-graphics sfml-window sfml-main music-storage json-storage)