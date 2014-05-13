cmake_minimum_required(VERSION 2.6)

file(GLOB_RECURSE HEADER_FILES *.h)
file(GLOB_RECURSE SOURCE_FILES *.cpp)

include_directories(${FRE_DEV_COMMON_DIR}
					${CMAKE_CURRENT_SOURCE_DIR}/../Engine/Include
					${FRE_MATH_DIRS})

add_executable(Test ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(Test Engine)