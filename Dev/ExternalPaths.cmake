SET(external_path "${CMAKE_CURRENT_SOURCE_DIR}/External")

#add glew find paths
LIST(APPEND CMAKE_INCLUDE_PATH "${external_path}/glew/include")
IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
	LIST(APPEND CMAKE_LIBRARY_PATH "${external_path}/glew/x64/Release")
ELSE()
	LIST(APPEND CMAKE_LIBRARY_PATH "${external_path}/glew/x86/Release")
ENDIF()
#add opengl find path
LIST(APPEND CMAKE_INCLUDE_PATH "${external_path}/OpenGL")
#add egl
LIST(APPEND CMAKE_LIBRARY_PATH "${external_path}/egl/x64/Release")
LIST(APPEND CMAKE_INCLUDE_PATH "${external_path}/egl/Include")
#add glm
LIST(APPEND CMAKE_INCLUDE_PATH "${external_path}/glm")
#add gtest
LIST(APPEND CMAKE_INCLUDE_PATH "${external_path}/gtest/include")
LIST(APPEND CMAKE_LIBRARY_PATH "${external_path}/gtest/lib")
