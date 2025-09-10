file(GLOB UTILS_SOURCES "*.cpp")
add_library(utils ${UTILS_SOURCES})

target_include_directories(utils PRIVATE "C:/SDL3/include")
target_link_libraries(utils PRIVATE "C:/SDL3/lib/x64/SDL3.lib")
target_link_libraries(utils PRIVATE "C:/SDL3/lib/x64/SDL3_image.lib")