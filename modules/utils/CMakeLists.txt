cmake_minimum_required(VERSION 3.2)
project(gcurve-utils)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()


add_library(gcurve-utils ${LIBRARY_ACTION}
        src/kspaceUtils.cpp)

target_include_directories(gcurve-utils PRIVATE
        include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(gcurve-utils
        -ldipacus-derivates
        -ldipacus-compponents
        -ldipacus-base
        ${DGTAL_LIBRARIES})

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS gcurve-utils
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)