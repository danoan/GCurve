cmake_minimum_required(VERSION 3.0)
project(gcurve)

#It expects variables
#CMAKE_PREFIX_PATH: find_[package] macro directories
#CMAKE_INSTALL_PREFIX: install location
#EXTRA_LINK_DIR: extra link directories
#BUILD_PATH: location of build files

find_package(DGtal REQUIRED)

link_directories(${EXTRA_LINK_DIR}
        ${BUILD_PATH}
        ext/lib)

set(BUILD_TEST OFF CACHE BOOL "Build tests.")

#SHARED LIBRARY
add_library(gcurve SHARED
        src/GluedCurveRange.cpp src/GluedCurve.cpp)

target_include_directories(gcurve PRIVATE
        include
        ext/include
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(gcurve
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        ${DGTAL_LIBRARIES})

set_target_properties(gcurve PROPERTIES
        COMPILE_FEATURES "cxx_auto_type;cxx_generic_lambdas"
        COMPILE_FLAGS -fext-numeric-literals)



install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS gcurve
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)


if (${BUILD_TEST})
    add_subdirectory(test)
endif()