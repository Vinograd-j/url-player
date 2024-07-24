add_library(music-storage STATIC src/json-music.cpp
        include/song.h
        include/music-storage.h
        src/song.cpp
)
target_include_directories(music-storage PUBLIC include)

target_link_libraries(music-storage PRIVATE json-storage)