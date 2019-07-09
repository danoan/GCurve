set(EXTPROJECTS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/ext-projects/source)
set(EXTPROJECTS_BUILD_DIR ${CMAKE_SOURCE_DIR}/ext-projects/build)

include(ExternalProject)
include(ext-projects/cmake-files/DIPaCUS.cmake)