cmake_minimum_required(VERSION 3.16)
project(MyGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

include(CPack)
set(CPACK_GENERATOR "ZIP")  # creates a zip package
set(CPACK_PACKAGE_NAME "MyGame")
set(CPACK_PACKAGE_VERSION "0.0.0")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
set(CPACK_NSIS_MENU_LINKS TRUE)

install(TARGETS game RUNTIME DESTINATION bin)  # for Windows

# install assets if you have any
install(DIRECTORY src/assets/ DESTINATION bin/assets)
install(FILES "C:/SDL3/lib/x64/SDL3.dll"
              "C:/SDL3/lib/x64/SDL3_image.dll"
              DESTINATION bin)