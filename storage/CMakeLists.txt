add_library(json-storage STATIC json-storage/src/storage-file.cpp
)
target_include_directories(json-storage PUBLIC json-storage/include json)

target_link_libraries(json-storage PRIVATE tgui)