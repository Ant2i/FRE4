cmake_minimum_required(VERSION 2.8)

set(PROJECT_TEST_NAME UTest)

file(GLOB_RECURSE HEADER_FILES *.h)
file(GLOB_RECURSE SOURCE_FILES *.cpp)

include_directories(${FRE_DEV_COMMON_DIR}
					${CMAKE_CURRENT_SOURCE_DIR}/../Engine/Include
					${FRE_MATH_DIRS}
					${GTEST_INCLUDE_DIRS})
					
add_definitions(${MSVC_COMPILER_DEFS})
add_executable(${PROJECT_TEST_NAME} ${HEADER_FILES} ${SOURCE_FILES})

add_dependencies(${PROJECT_TEST_NAME} googletest)

if (WIN32)
	target_link_libraries(${PROJECT_TEST_NAME} debug ${GTEST_LIBS_DIR}/Debug/gtest.lib optimized ${GTEST_LIBS_DIR}/Release/gtest.lib)
	target_link_libraries(${PROJECT_TEST_NAME} debug ${GTEST_LIBS_DIR}/Debug/gtest_main.lib optimized ${GTEST_LIBS_DIR}/Release/gtest_main.lib)
else()
	target_link_libraries(${PROJECT_TEST_NAME} debug ${GTEST_LIBS_DIR}/Debug/libgtest.a optimized ${GTEST_LIBS_DIR}/Release/libgtest.a)
	target_link_libraries(${PROJECT_TEST_NAME} debug ${GTEST_LIBS_DIR}/Debug/libgtest_main.a optimized ${GTEST_LIBS_DIR}/Release/libgtest_main.a)
endif()

target_link_libraries(${PROJECT_TEST_NAME} Engine)