cmake_minimum_required(VERSION 2.8)

file(GLOB HEADER_FILES *.h)
file(GLOB SOURCE_FILES *.cpp)

find_package(OpenGL REQUIRED)
#find_package(GLEW REQUIRED)

include_directories(
	${FRE_DEV_COMMON_DIR}
	${FRE_MATH_DIRS}
	${CMAKE_CURRENT_SOURCE_DIR}/Include
	${CMAKE_CURRENT_SOURCE_DIR}/../Engine/Include
	${OPENGL_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS})

add_definitions(-D_USE_MATH_DEFINES)

add_library(GLRenderDevice SHARED ${HEADER_FILES} ${SOURCE_FILES} ${PLATFORM_HEADERS} ${PLATFORM_SOURCES})

#message(${GLEW_LIBRARIES})

target_link_libraries(GLRenderDevice ${OPENGL_LIBRARIES})
#target_link_libraries(GLRenderDevice ${GLEW_LIBRARIES})