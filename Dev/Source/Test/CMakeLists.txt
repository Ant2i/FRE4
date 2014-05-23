cmake_minimum_required(VERSION 2.6)

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

if (NOT WIN32)
	target_link_libraries(${PROJECT_TEST_NAME} pthread)
	target_link_libraries(${PROJECT_TEST_NAME} ${GTEST_LIBS_DIR}/libgtest.a ${GTEST_LIBS_DIR}/libgtest_main.a)
else()
	target_link_libraries(${PROJECT_TEST_NAME}
	       debug ${GTEST_LIBS_DIR}/Debug/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES}
	       optimized ${GTEST_LIBS_DIR}/Release/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${CMAKE_FIND_LIBRARY_SUFFIXES})
	target_link_libraries(${PROJECT_TEST_NAME}
	       debug ${GTEST_LIBS_DIR}/Debug/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES}
	       optimized ${GTEST_LIBS_DIR}/Release/${CMAKE_FIND_LIBRARY_PREFIXES}gtest_main${CMAKE_FIND_LIBRARY_SUFFIXES})
endif()

target_link_libraries(${PROJECT_TEST_NAME} Engine)