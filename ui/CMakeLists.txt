add_library(ui STATIC
        src/music-list.cpp
        src/button.cpp
        ui-config/src/json-menu-config.cpp
        src/menu.cpp
        src/music-panel.cpp
        ui-config/src/json-music-panel-config.cpp
        src/confirmation-window.cpp
        include/confirmation-window.h
        ui-config/src/ui-json-serializer.cpp
        ui-config/include/ui-json-serializer.h
)

target_include_directories(ui PUBLIC ${TGUI_INCLUDE_DIR} ${SFML_INCLUDE_DIR} include ${CMAKE_SOURCE_DIR}/json ui-config/include)

target_link_libraries(ui PRIVATE tgui sfml-system sfml-graphics sfml-window sfml-main music-storage json-storage player nlohmann_json::nlohmann_json)