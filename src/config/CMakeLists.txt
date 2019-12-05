find_package(jsoncpp CONFIG REQUIRED)

set(CMAKE_VERBOSE_MAKEFILE 1)
set(LIB_SONAME ConfigFile)
set(LIB_SRCs ConfigFile.cpp )

add_library(${LIB_SONAME} ${LIB_SRCs})
target_link_libraries(${LIB_SONAME} jsoncpp)

if (TEST_CONFIG_CODE)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
    add_executable(testConfigLib testConfigLib.cpp)
    target_link_libraries(testConfigLib ConfigFile)
endif(TEST_CONFIG_CODE)