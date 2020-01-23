cmake_minimum_required(VERSION 3.2)
project(gcurve-utils)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()


add_library(gcurve-utils ${LIBRARY_ACTION}
        src/kspaceUtils.cpp)

if (${USE_REMOTE_REPOSITORIES})
    add_dependencies(gcurve-utils dipacus)
endif()

target_include_directories(gcurve-utils PRIVATE
        include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(gcurve-utils
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        ${DGTAL_LIBRARIES})

set_target_properties(gcurve-utils PROPERTIES
        VERSION ${VERSION_GCURVE_UTILS})

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS gcurve-utils
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)