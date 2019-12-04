cmake_minimum_required(VERSION 3.12)
project(ReducedSpaceSimulation)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_VERBOSE_MAKEFILE 0)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

message(STATUS "CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")
message(STATUS "EXECUTABLE_OUTPUT_PATH = ${EXECUTABLE_OUTPUT_PATH}")
message(STATUS "LIBRARY_OUTPUT_PATH = ${LIBRARY_OUTPUT_PATH}")
message(STATUS "PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")

include_directories(${PROJECT_SOURCE_DIR})

#add_subdirectory(${PROJECT_SOURCE_DIR}/basis)
add_subdirectory(${PROJECT_SOURCE_DIR}/config)
#add_subdirectory(${PROJECT_SOURCE_DIR}/contact)
#add_subdirectory(${PROJECT_SOURCE_DIR}/cubature)
#add_subdirectory(${PROJECT_SOURCE_DIR}/integrator)
#add_subdirectory(${PROJECT_SOURCE_DIR}/latentDynamcs)
#add_subdirectory(${PROJECT_SOURCE_DIR}/openGLHelper)
add_subdirectory(${PROJECT_SOURCE_DIR}/utility)

