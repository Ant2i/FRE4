cmake_minimum_required(VERSION 2.6)

set(FRE_DEV_COMMON_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Common")

set(FRE_ENGINE_INSTALL_INCLUDE_DIRS "${CMAKE_BINARY_DIR}/InstallInclude")
#message("--->" ${FRE_ENGINE_INSTALL_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR} ${CMAKE_BINARY_DIR})

add_subdirectory(Engine)
add_subdirectory(RenderGL)
add_subdirectory(Test)