include(ExternalProject)

cmake_minimum_required(VERSION 3.22.1)

project("myapplication")

# Build libass
ExternalProject_Add(
        libass_external
        PREFIX libass
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libass
        INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libass/install
        BUILD_IN_SOURCE 1
        CONFIGURE_COMMAND CC=${CMAKE_C_COMPILER} CXX=${CMAKE_CXX_COMPILER} AR=${CMAKE_AR} meson setup build -Drequire-system-font-provider=false --prefix ${CMAKE_CURRENT_SOURCE_DIR}/libass/install --reconfigure --cross-file ../cross_file.txt
        BUILD_COMMAND ninja -C build
        BUILD_ALWAYS true
        INSTALL_COMMAND ninja -C build install
        BUILD_BYPRODUCTS ${CMAKE_CURRENT_SOURCE_DIR}/libass/build/libass/libass.a
)

add_library(libass STATIC IMPORTED)
set_target_properties(libass PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/libass/build/libass/libass.a)
add_dependencies(libass libass_external)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libass/build/libass)
# End build libass

add_library(${CMAKE_PROJECT_NAME} SHARED
        native-lib.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        log
        jnigraphics
        libass
        )
