cmake_minimum_required(VERSION 3.0)
project(gcurve)

set(DIPACUS_INCLUDE_DIR ext/include CACHE PATH "Path to DIPaCUS include directory.")
set(DIPACUS_LIB_DIR ext/lib CACHE PATH "Path to DIPaCUS library directory.")
set(MAGICK++_INCLUDE_DIR /usr/include/GraphicsMagick CACHE PATH "Magick++ include folder.")

link_directories(${DIPACUS_LIB_DIR}
        cmake-build-debug)

add_library(gcurve STATIC
        src/GluedCurveRange.cpp src/GluedCurve.cpp)

target_include_directories(gcurve PRIVATE
        include
        ext/include
        ${MAGICK++_INCLUDE_DIR}
        ${DIPACUS_INCLUDE_DIR}
        ${DIPACUS_INCLUDE_DIR})

target_link_libraries(gcurve
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        ${DGTAL_LIBRARIES})

set_target_properties(gcurve PROPERTIES
        COMPILE_FEATURES "cxx_auto_type;cxx_generic_lambdas"
        COMPILE_FLAGS -fext-numeric-literals)

add_subdirectory(test)

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS gcurve
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
