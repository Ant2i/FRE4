FUNCTION(GENERATE_API target)
	GET_TARGET_PROPERTY(sources ${target} SOURCES)
	
	SET(api_path ${PROJECT_BINARY_DIR}/API)
	SET(api_template_sub_path "/Public")
	STRING(LENGTH ${api_template_sub_path} template_len)
	
	FOREACH(source_file ${sources})
		GET_FILENAME_COMPONENT(file_directory ${source_file} DIRECTORY)
		GET_FILENAME_COMPONENT(file_name ${source_file} NAME)
		
		STRING(LENGTH ${file_directory} file_directory_len)
		
		IF (${template_len} LESS ${file_directory_len})
			MATH(EXPR begin_pos "${file_directory_len}-${template_len}")
			STRING(SUBSTRING ${file_directory} ${begin_pos} ${template_len} sub_dir)
			
			IF (${sub_dir} STREQUAL ${api_template_sub_path})
								
				FILE(RELATIVE_PATH relative_path ${PROJECT_SOURCE_DIR}/Source ${file_directory})
				STRING(REPLACE ${api_template_sub_path} "" relative_path ${relative_path})
				
				FILE(RELATIVE_PATH relative_source ${api_path}/${relative_path} ${source_file})
				FILE(WRITE ${api_path}/${relative_path}/${file_name} "#include @relative_source@" )
			ENDIF()
		ENDIF()
		
		
		#message(${file_directory} | ${file_name})
	ENDFOREACH()	
ENDFUNCTION()