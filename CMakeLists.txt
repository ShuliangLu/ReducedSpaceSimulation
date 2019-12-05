cmake_minimum_required(VERSION 3.12)

set(CMAKE_TOOLCHAIN_FILE ${_VCPKG_TOOLCHAIN_DIR}/vcpkg.cmake)
project(ReducedSpaceSimulation)
include_directories(${_VCPKG_INSTALLED_DIR}/x64-linux/include)
link_directories(${_VCPKG_INSTALLED_DIR}/x64-linux/lib)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE 0)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ${CMAKE_SOURCE_DIR}/src)
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${CMAKE_SOURCE_DIR}/lib)

#message(STATUS "CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")
#message(STATUS "EXECUTABLE_OUTPUT_PATH = ${EXECUTABLE_OUTPUT_PATH}")
#message(STATUS "LIBRARY_OUTPUT_PATH = ${LIBRARY_OUTPUT_PATH}")
#message(STATUS "PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message(STATUS "CMAKE_LIBRARY_PATH = ${CMAKE_LIBRARY_PATH}")

#configure_file ( "${PROJECT_SOURCE_DIR}/config.h.in" "${CMAKE_BINARY_DIR}/config.h" )
#
option(TEST_CONFIG_CODE "Test the ConfigFile library" ON)
#
if(COMPILE_LIB_TEST_CODE)
    message(STATUS,"Compile lib test example")
else(COMPILE_LIB_TEST_CODE)
    message(STATUS "Won't compile lib test example v[${COMPILE_LIB_TEST_CODE}]")
endif(COMPILE_LIB_TEST_CODE)

include_directories(${PROJECT_SOURCE_DIR})
#add_subdirectory(${PROJECT_SOURCE_DIR}/basis)
add_subdirectory(${PROJECT_SOURCE_DIR}/config)
#add_subdirectory(${PROJECT_SOURCE_DIR}/contact)
#add_subdirectory(${PROJECT_SOURCE_DIR}/cubature)
#add_subdirectory(${PROJECT_SOURCE_DIR}/integrator)
#add_subdirectory(${PROJECT_SOURCE_DIR}/latentDynamcs)
#add_subdirectory(${PROJECT_SOURCE_DIR}/openGLHelper)
add_subdirectory(${PROJECT_SOURCE_DIR}/utility)


