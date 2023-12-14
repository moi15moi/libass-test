include(ExternalProject)

cmake_minimum_required(VERSION 3.22.1)

project("myapplication")



# ExternalProject_Add command to build the Meson-based project
ExternalProject_Add(
        libass
        PREFIX libass
        SOURCE_DIR libass
        CONFIGURE_COMMAND meson setup ./libass ./libass/build -Drequire-system-font-provider=false
        BUILD_COMMAND ninja -C libass/build
        INSTALL_COMMAND ninja -C libass/build install
)


add_library(${CMAKE_PROJECT_NAME} SHARED
        native-lib.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        log
        jnigraphics)