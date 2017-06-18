SET(target_name HRI)

ADD_LIBRARY(${target_name} INTERFACE)

SET(out_rd_impl_dir ${CMAKE_CURRENT_BINARY_DIR})

TARGET_INCLUDE_DIRECTORIES(${target_name}
    INTERFACE
		$<BUILD_INTERFACE:;${CMAKE_CURRENT_SOURCE_DIR}/Public;${out_rd_impl_dir};../Misc;>
)

ADD_SUBDIRECTORY(OpenGL)
#ADD_SUBDIRECTORY(Vulkan)
