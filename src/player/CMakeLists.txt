file(GLOB PLAYER_SOURCES "*.cpp")
add_library(player ${PLAYER_SOURCES})

target_include_directories(player PRIVATE "C:/SDL3/include")
target_link_libraries(player PRIVATE "C:/SDL3/lib/x64/SDL3.lib")
target_link_libraries(player PRIVATE "C:/SDL3/lib/x64/SDL3_image.lib")