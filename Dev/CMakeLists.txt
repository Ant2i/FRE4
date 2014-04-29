cmake_minimum_required(VERSION 2.6)
project(FRE4)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Common)

if (CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-std=c++0x)
	add_definitions(-DSTRONGLY_TYPED_ENUMS_SUPPORTED)
endif()

#set(INCLUDE_CMAKE ${CMAKE_ROOT}/CMake)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")

# Config math library
#include(${INCLUDE_CMAKE}/FindGLM.cmake)
find_package(GLM)

add_subdirectory(Source)
