﻿CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(TARGET_NAME FreGraph)

FILE(GLOB_RECURSE FILES Include/*.* Source/*.*)

ADD_LIBRARY(${TARGET_NAME} SHARED ${FILES})

GENERATE_EXPORT_HEADER(${TARGET_NAME} BASE_NAME graph)

TARGET_INCLUDE_DIRECTORIES(${TARGET_NAME}
	PUBLIC 
		Include
		${CMAKE_CURRENT_BINARY_DIR}
)

TARGET_LINK_LIBRARIES(${TARGET_NAME} 
	FreUtils
)
