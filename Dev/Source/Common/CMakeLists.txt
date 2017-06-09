CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(target_name Common)

FILE(GLOB_RECURSE files Public/*.* Private/*.*)

ADD_LIBRARY(${target_name} STATIC ${files})
SET_TARGET_PROPERTIES(${target_name} PROPERTIES LINKER_LANGUAGE CXX)

TARGET_INCLUDE_DIRECTORIES(${target_name}
	PRIVATE 
		Public
)

GENERATE_API(${target_name})