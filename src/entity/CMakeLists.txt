file(GLOB ENTITY_SOURCES "*.cpp")
add_library(entity ${ENTITY_SOURCES})

target_include_directories(entity PRIVATE "C:/SDL3/include")
target_link_libraries(entity PRIVATE "C:/SDL3/lib/x64/SDL3.lib")
target_link_libraries(entity PRIVATE "C:/SDL3/lib/x64/SDL3_image.lib")