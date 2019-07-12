cmake_minimum_required(VERSION 3.2)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

set(BOOST_INCLUDE_DIRS /usr/local/include/boost CACHE PATH "Boost include location path." )
set(BOOST_LIBS_DIR /usr/local/lib CACHE PATH "Boost libraries location path." )

set(DIPACUS_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/ext-projects/build/include CACHE PATH "DIPaCUS include location path.")
set(DIPACUS_LIBS_DIR ${CMAKE_SOURCE_DIR}/ext-projects/build/lib CACHE PATH "DIPaCUS libraries location path.")

set(BUILD_TESTS OFF CACHE BOOL "Build tests.")
set(CREATE_SHARED_LIBRARIES ON CACHE BOOL "Create shared libraries. If off, create static libraries.")
set(USE_REMOTE_REPOSITORIES ON CACHE BOOL "Pull external repositories from GitHub.")

project(gcurve)

message("Project Root Dir: ${CMAKE_SOURCE_DIR}")
message("Build files at: ${CMAKE_BINARY_DIR}")
message("Installation at: ${CMAKE_INSTALL_PREFIX}")

if (${USE_REMOTE_REPOSITORIES})
    include(ext-projects/ExtProjects.cmake)
endif()

find_package(DGtal REQUIRED)

link_directories(
        ${CMAKE_BINARY_DIR}/modules/core
        ${CMAKE_BINARY_DIR}/modules/utils
        ${DIPACUS_LIBS_DIR}
        ${BOOST_LIBS_DIR}
        ${CMAKE_PREFIX_PATH})


add_subdirectory(modules/core)
add_subdirectory(modules/utils)


if (${BUILD_TESTS})
    add_subdirectory(lab/test)
    add_subdirectory(lab/examples)
endif()