cmake_minimum_required(VERSION 3.0)
project(test-gcurve)

add_executable(tests-main
        main.cpp
        src/model/GCAttributes.cpp
        src/utils/EstimateCurvature.cpp
        src/control/GCAttributeWriter.cpp
        src/control/GCAttributeReader.cpp
        src/testExecution.cpp
        src/testCorrecteness.cpp)

if (${USE_LOCAL_REPOSITORIES})
    add_dependencies(tests-main dipacus gcurve)
else()
    add_dependencies(tests-main gcurve)
endif()

target_compile_definitions(tests-main PRIVATE -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

target_include_directories(tests-main PUBLIC
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS} )

set_target_properties(tests-main PROPERTIES
        COMPILE_FEATURES "cxx_auto_type;cxx_generic_lambdas"
        COMPILE_FLAGS -fext-numeric-literals)

target_link_libraries(tests-main
        -lgcurve
        -lgcurve-utils
        -ldipacus-derivates
        -ldipacus-components
        -ldipacus-base
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})
