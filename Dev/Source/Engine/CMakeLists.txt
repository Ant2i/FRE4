cmake_minimum_required(VERSION 2.6)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/Include/config.h)

file(GLOB_RECURSE HEADER_FILES Include/*.h)
file(GLOB_RECURSE SOURCE_FILES Source/*.*)

include_directories(
	${FRE_MATH_DIRS}
	${CMAKE_CURRENT_SOURCE_DIR}/Include
	)
  
add_definitions(-D_FRE4_EXPORTS)
add_definitions(-D_USE_MATH_DEFINES)

add_library(Engine SHARED ${HEADER_FILES} ${SOURCE_FILES} ${PLATFORM_HEADERS} ${PLATFORM_SOURCES})