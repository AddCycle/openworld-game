file(GLOB FONT_SOURCES "*.cpp")
add_library(font ${FONT_SOURCES})

target_include_directories(font PRIVATE "C:/SDL3/include")
target_link_libraries(font PRIVATE "C:/SDL3/lib/x64/SDL3.lib")
target_link_libraries(font PRIVATE "C:/SDL3/lib/x64/SDL3_image.lib")
target_link_libraries(font PRIVATE "C:/SDL3/lib/x64/SDL3_ttf.lib")