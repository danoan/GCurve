cmake_minimum_required(VERSION 3.0)
project(examples-gcurve)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)


add_executable(examples-countGCurves countGCurves.cpp )
target_compile_definitions(examples-countGCurves PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

add_executable(examples-drawGCurves drawGCurves.cpp)
target_compile_definitions(examples-drawGCurves PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

set_target_properties(examples-countGCurves examples-drawGCurves PROPERTIES
        COMPILE_FEATURES "cxx_auto_type;cxx_generic_lambdas"
        COMPILE_FLAGS -fext-numeric-literals)


target_include_directories(examples-countGCurves PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/dev/include
        ${CMAKE_SOURCE_DIR}/ext/include
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(examples-countGCurves
        -lgcurve
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})


target_include_directories(examples-drawGCurves PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/dev/include
        ${CMAKE_SOURCE_DIR}/ext/include
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(examples-drawGCurves
        -lgcurve
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lboost_system
        -lboost_filesystem
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})