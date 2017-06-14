CMAKE_MINIMUM_REQUIRED(VERSION 2.8.2)

PROJECT(googletest-download NONE)

INCLUDE(ExternalProject)

ExternalProject_Add(googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           master
  PREFIX 			${CMAKE_BINARY_DIR}/External/googletest
  CMAKE_ARGS   -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -Dgtest_force_shared_crt=ON
			   -D_VARIADIC_MAX=10
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(googletest source_dir binary_dir)

message(${binary_dir})
message(${source_dir})

SET(bin_location ${binary_dir}/googlemock/gtest)
SET(include_location ${source_dir}/googletest/include)

ADD_LIBRARY(libgtest IMPORTED STATIC GLOBAL)
ADD_DEPENDENCIES(libgtest googletest)

SET(gtest_library ${bin_location}/Release/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX})
SET(gtest_library_d ${bin_location}/Debug/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX})
SET(gtest_main_library ${bin_location}/Release/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX})
SET(gtest_main_library_d ${bin_location}/Debug/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX})

SET_TARGET_PROPERTIES(libgtest PROPERTIES
		IMPORTED_LOCATION ${gtest_main_library}
		IMPORTED_LOCATION_DEBUG ${gtest_main_library_d}
		INTERFACE_INCLUDE_DIRECTORIES ${include_location}
		IMPORTED_LINK_INTERFACE_LIBRARIES "${gtest_library};${CMAKE_THREAD_LIBS_INIT}"
		IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "${gtest_library_d};${CMAKE_THREAD_LIBS_INIT}"
)

# Create a libgmock target to be used as a dependency by test programs
ADD_LIBRARY(libgmock IMPORTED STATIC GLOBAL)
ADD_DEPENDENCIES(libgmock googletest)

# Set libgmock properties
SET_TARGET_PROPERTIES(libgmock PROPERTIES
    IMPORTED_LOCATION "${binary_dir}/googlemock/libgmock.a"
    IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
)