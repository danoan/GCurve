cmake_minimum_required(VERSION 3.2)
project(gcurve_lib)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()

add_library(gcurve ${LIBRARY_ACTION}
        src/Range.cpp
        src/GluedCurve.cpp)

add_dependencies(gcurve gcurve-utils)

target_include_directories(gcurve PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(gcurve
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        ${DGTAL_LIBRARIES})

set_target_properties(gcurve PROPERTIES
        COMPILE_FEATURES "cxx_auto_type;cxx_generic_lambdas"
        COMPILE_FLAGS -fext-numeric-literals
        VERSION ${VERSION_GCURVE_CORE})



install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS gcurve
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)