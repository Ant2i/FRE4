﻿CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

FILE(GLOB SRC *.cpp *.h)

ADD_EXECUTABLE(Platform_Test ${SRC})

TARGET_LINK_LIBRARIES(Platform_Test 
	Platform
	libgtest
)
