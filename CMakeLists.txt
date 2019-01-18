cmake_minimum_required(VERSION 3.0)
project(gcurve)

#CMAKE_INSTALL_PREFIX: install location

message("Project Root Dir: ${CMAKE_SOURCE_DIR}")
message("Build files at: ${CMAKE_BINARY_DIR}")
message("Installation at: ${CMAKE_INSTALL_PREFIX}")

find_package(DGtal REQUIRED)

set(BOOST_INCLUDE_DIRS /usr/local/include/boost CACHE PATH "Boost include location path." )

set(DIPACUS_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/ext/include CACHE PATH "DIPaCUS include location path.")
set(DIPACUS_LIBS_DIR /usr/local/lib CACHE PATH "DIPaCUS libraries location path.")

set(BUILD_TESTS OFF CACHE BOOL "Build tests.")

link_directories(${CMAKE_BINARY_DIR}
        ${DIPACUS_LIBS_DIR})


#SHARED LIBRARY
add_library(gcurve SHARED
        src/GluedCurveRange.cpp src/GluedCurve.cpp)

target_include_directories(gcurve PRIVATE
        include
        ${DIPACUS_INCLUDE_DIRS}
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


if (${BUILD_TESTS})
    add_subdirectory(test)
    add_subdirectory(examples)
endif()