set(LIB_SONAME configuration)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRCs)
message(STATUS "SRCs = ${SRCs}")
add_library(${LIB_SONAME} SHARED ${SRCs})

