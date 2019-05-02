cmake_minimum_required(VERSION 3.0)
project(gcurve)

#CMAKE_INSTALL_PREFIX: install location
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

message("Project Root Dir: ${CMAKE_SOURCE_DIR}")
message("Build files at: ${CMAKE_BINARY_DIR}")
message("Installation at: ${CMAKE_INSTALL_PREFIX}")

find_package(DGtal REQUIRED)

set(BOOST_INCLUDE_DIRS /usr/local/include/boost CACHE PATH "Boost include location path." )
set(BOOST_LIBS_DIR /usr/local/lib CACHE PATH "Boost libraries location path." )

set(DIPACUS_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/ext/include CACHE PATH "DIPaCUS include location path.")
set(DIPACUS_LIBS_DIR /usr/local/lib CACHE PATH "DIPaCUS libraries location path.")

set(BUILD_TESTS OFF CACHE BOOL "Build tests.")
set(CREATE_SHARED_LIBRARIES OFF CACHE BOOL "Create shared libraries. If off, create static libraries.")

link_directories(
        ${CMAKE_BINARY_DIR}/dev
        ${DIPACUS_LIBS_DIR}
        ${BOOST_LIBS_DIR}
        ${CMAKE_PREFIX_PATH})


add_subdirectory(dev)


if (${BUILD_TESTS})
    add_subdirectory(test)
    add_subdirectory(examples)
endif()