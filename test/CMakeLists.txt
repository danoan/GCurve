cmake_minimum_required(VERSION 3.0)
project(test-gcurve)

add_executable(tests-main main.cpp src/testUtils.cpp src/testExecution.cpp src/testCorrecteness.cpp)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

target_compile_definitions(tests-main PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

target_include_directories(tests-main PUBLIC
        include
        ../include
        ../ext/include
        ${MAGICK++_INCLUDE_DIR} )

set_target_properties(tests-main PROPERTIES
        COMPILE_FEATURES "cxx_auto_type;cxx_generic_lambdas"
        COMPILE_FLAGS -fext-numeric-literals)

target_link_libraries(tests-main
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        -lgcurve
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})
