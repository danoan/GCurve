cmake_minimum_required(VERSION 3.2)
project(example-drawGCcurves)

add_executable(examples-drawGCurves drawGCurves.cpp)
add_dependencies(examples-drawGCurves gcurve gcurve-utils)
target_compile_definitions(examples-drawGCurves PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")


target_include_directories(examples-drawGCurves PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_directories(examples-drawGCurves PRIVATE
        ${BOOST_LIBS_DIR})

target_link_libraries(examples-drawGCurves
        -lgcurve
        -lgcurve-utils
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_system
        -lboost_filesystem
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})