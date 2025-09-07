file(GLOB CAMERA_SOURCES "*.cpp")
add_library(camera ${CAMERA_SOURCES})

target_include_directories(camera PRIVATE "C:/SDL3/include")
target_link_libraries(camera PRIVATE "C:/SDL3/lib/x64/SDL3.lib")
target_link_libraries(camera PRIVATE "C:/SDL3/lib/x64/SDL3_image.lib")