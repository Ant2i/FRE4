cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE HEADER_FILES Include/*.h)
file(GLOB_RECURSE SOURCE_FILES Source/*.*)

list(REMOVE_AT HEADER_FILES config.h)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/Include/config.h)

include_directories(
	${FRE_DEV_COMMON_DIR}
	${FRE_MATH_DIRS}
	${CMAKE_CURRENT_SOURCE_DIR}/Include)
  
add_definitions(-D_FRE4_EXPORTS)
add_definitions(-D_USE_MATH_DEFINES)

add_library(${ENGINE_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})