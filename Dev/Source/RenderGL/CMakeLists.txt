cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE HEADER_FILES *.h)
file(GLOB_RECURSE SOURCE_FILES *.cpp)

find_package(OpenGL REQUIRED)

include_directories(
	${FRE_DEV_COMMON_DIR}
	${FRE_MATH_DIRS}
	${CMAKE_CURRENT_SOURCE_DIR}/Include
	${CMAKE_CURRENT_SOURCE_DIR}/../Engine/Include
	${OpenGL_INCLUDE_DIRS})

link_directories(${OpenGL_LIBRARY_DIRS})

add_definitions(-D_USE_MATH_DEFINES)
add_library(GLRenderDevice SHARED ${HEADER_FILES} ${SOURCE_FILES} ${PLATFORM_HEADERS} ${PLATFORM_SOURCES})

target_link_libraries(GLRenderDevice ${OPENGL_LIBRARIES})