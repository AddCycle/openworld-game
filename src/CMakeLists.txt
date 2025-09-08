file(GLOB SDL_SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/sdl/*.cpp")

# add_executable(game WIN32 ${SDL_SOURCES})
add_executable(game ${SDL_SOURCES})

add_subdirectory(player)
add_subdirectory(entity)
# add_subdirectory(sdl)
add_subdirectory(map)
add_subdirectory(camera)
add_subdirectory(font)

target_link_libraries(game PRIVATE player)
target_link_libraries(game PRIVATE entity)
# target_link_libraries(game PRIVATE sdl)
target_link_libraries(game PRIVATE map)
target_link_libraries(game PRIVATE camera)
target_link_libraries(game PRIVATE font)

# Include SDL3 headers
target_include_directories(game PRIVATE "C:/SDL3/include")

# Link against the import library for the DLL
target_link_libraries(game PRIVATE "C:/SDL3/lib/x64/SDL3.lib")
target_link_libraries(game PRIVATE "C:/SDL3/lib/x64/SDL3_image.lib")
target_link_libraries(game PRIVATE "C:/SDL3/lib/x64/SDL3_ttf.lib")

# Copy the DLL next to the executable automatically
add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "C:/SDL3/lib/x64/SDL3.dll"
    $<TARGET_FILE_DIR:game>)

# SDL3_image lib also
add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "C:/SDL3/lib/x64/SDL3_image.dll"
    $<TARGET_FILE_DIR:game>)

# SDL3_ttf for writing things on the screen
add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "C:/SDL3/lib/x64/SDL3_ttf.dll"
    $<TARGET_FILE_DIR:game>)

# copy all the assets inside the build dir
add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/src/assets"
    $<TARGET_FILE_DIR:game>/assets
)

# copy the map inside build
add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/tiled"
    $<TARGET_FILE_DIR:game>/tiled
)