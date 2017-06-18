CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

SET(project_name Image)

FIND_PACKAGE(FreeImage REQUIRED)

FILE(GLOB_RECURSE header_files Public/*.*)
FILE(GLOB_RECURSE source_files Private/*.*)

ADD_DEFINITIONS(-DIMAGE_EXPORTS -D_USE_MATH_DEFINES -D_IMAGE_EXPORTS)

ADD_LIBRARY(${project_name} SHARED ${header_files} ${source_files})

TARGET_INCLUDE_DIRECTORIES(${project_name} 
	PUBLIC
		Public
	PRIVATE 
		${FREEIMAGE_INCLUDE_DIR}
)

TARGET_LINK_LIBRARIES(${project_name} ${FREEIMAGE_LIBRARY})

IF (unit_tests)
	ADD_SUBDIRECTORY(Test)
ENDIF()

IF (PLATFORM_WIN)
	STRING(REPLACE ".lib" ".dll" freeimage_dll ${FREEIMAGE_LIBRARY})
	#Copy freeimage dll
	ADD_CUSTOM_COMMAND(TARGET ${project_name} POST_BUILD 
               COMMAND ${CMAKE_COMMAND} -E copy_if_different
               ${freeimage_dll}              
               $<TARGET_FILE_DIR:${project_name}>)
ENDIF()

INSTALL(TARGETS ${project_name}
		RUNTIME DESTINATION	"Image")
