#
# Try to find the FreeImage library and include path.
# Once done this will define
#
# FREEIMAGE_FOUND
# FREEIMAGE_INCLUDE_DIR
# FREEIMAGE_LIBRARY
# 

IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
  SET(ARCH "x64" CACHE STRING "CPU Architecture")
ELSE()
  SET(ARCH "x32" CACHE STRING "CPU Architecture")
ENDIF()

IF (WIN32)
	FIND_PATH(FREEIMAGE_INCLUDE_DIR FreeImage.h
		${PROJECT_SOURCE_DIR}/extern/FreeImage/Dist/${ARCH}
		${PROJECT_SOURCE_DIR}/external/FreeImage/Dist/${ARCH}
		${PROJECT_SOURCE_DIR}/external/FreeImage/Include
		DOC "The directory where FreeImage.h resides"
	)
		
	FIND_LIBRARY(FREEIMAGE_LIBRARY
		NAMES FreeImage freeimage freeimagelib
		PATHS
		${PROJECT_SOURCE_DIR}/extern/FreeImage/Dist/${ARCH}
		${PROJECT_SOURCE_DIR}/external/FreeImage/Dist/${ARCH}
		${PROJECT_SOURCE_DIR}/external/FreeImage/${ARCH}
		DOC "The FreeImage library"
	)
ELSE()
	FIND_PATH(FREEIMAGE_INCLUDE_DIR FreeImage.h
		/usr/include
		/usr/local/include
		/sw/include
		/opt/local/include
		DOC "The directory where FreeImage.h resides"
	)
	
	FIND_LIBRARY(FREEIMAGE_LIBRARY
		NAMES FreeImage freeimage
		PATHS
		/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
		DOC "The FreeImage library"
	)
ENDIF()

SET(FREEIMAGE_LIBRARIES ${FREEIMAGE_LIBRARY})

IF (FREEIMAGE_INCLUDE_DIR AND FREEIMAGE_LIBRARY)
	SET(FREEIMAGE_FOUND TRUE CACHE BOOL "Set to TRUE if GLEW is found, FALSE otherwise")
ELSE()
	SET(FREEIMAGE_FOUND FALSE CACHE BOOL "Set to TRUE if GLEW is found, FALSE otherwise")
ENDIF() 

MARK_AS_ADVANCED(
	FREEIMAGE_FOUND 
	FREEIMAGE_LIBRARY
	FREEIMAGE_LIBRARIES
	FREEIMAGE_INCLUDE_DIR
)