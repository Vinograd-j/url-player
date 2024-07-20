add_library(storage STATIC src/json-storage.cpp)

target_include_directories(storage PRIVATE include json)