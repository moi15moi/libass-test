include(ExternalProject)

cmake_minimum_required(VERSION 3.22.1)

project("myapplication")


ExternalProject_Add(
        libass
        PREFIX libass
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libass
        BUILD_IN_SOURCE 1
        CONFIGURE_COMMAND meson setup build -Drequire-system-font-provider=false
        BUILD_COMMAND ninja -C build
        INSTALL_COMMAND ninja -C build install
)


add_library(${CMAKE_PROJECT_NAME} SHARED
        native-lib.cpp)

add_dependencies(${CMAKE_PROJECT_NAME} libass)

target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        log
        jnigraphics
        ${CMAKE_CURRENT_SOURCE_DIR}/libass/build/libass/libass.a)