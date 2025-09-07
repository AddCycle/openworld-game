file(GLOB MAP_SOURCES "*.cpp")
add_library(map ${MAP_SOURCES})

target_include_directories(map PRIVATE "C:/SDL3/include")
target_link_libraries(map PRIVATE "C:/SDL3/lib/x64/SDL3.lib")
target_link_libraries(map PRIVATE "C:/SDL3/lib/x64/SDL3_image.lib")