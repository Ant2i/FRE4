cmake_minimum_required(VERSION 2.6)

file(GLOB_RECURSE HEADER_FILES *.h)
file(GLOB_RECURSE SOURCE_FILES *.cpp)

include_directories(${FRE_ENGINE_INSTALL_INCLUDE_DIRS})

add_executable(Test ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(Test Engine)