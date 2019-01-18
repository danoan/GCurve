cmake_minimum_required(VERSION 3.0)
project(examples-gcurve)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)


add_executable(examples-main main.cpp ../src/GluedCurveRange.cpp ../src/GluedCurve.cpp)

target_compile_definitions(examples-main PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

set_target_properties(examples-main PROPERTIES
        COMPILE_FEATURES "cxx_auto_type;cxx_generic_lambdas"
        COMPILE_FLAGS -fext-numeric-literals)

target_include_directories(examples-main PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/ext/include
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(examples-main
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})
