cmake_minimum_required(VERSION 2.8)

find_package(GLM)
if (GLM_FOUND)
	set(FRE_MATH_DIRS ${GLM_INCLUDE_DIRS})
	set(FRE_MATH_H "${FRE_EXTERNAL_PATH}/Math/MathGLM.h")
endif()

set(FRE_DEV_COMMON_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Common")
set(FRE_DEV_DIRS ${FRE_DEV_COMMON_DIR} ${FRE_MATH_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/Engine/Include")

add_subdirectory(Engine)
add_subdirectory(RenderGL)
add_subdirectory(Test)
add_subdirectory(Demo)