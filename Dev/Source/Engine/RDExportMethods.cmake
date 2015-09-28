CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

SET(IN_RD_DEF_NAME "Include/RD/RDMethods.h")
SET(OUT_RD_IMPL_NAME "Include/RD/RDMethodsDefs_autogen.inc")



FILE(REMOVE ${OUT_RD_IMPL_NAME})
FILE(READ ${IN_RD_DEF_NAME} RDMethods)
STRING(REGEX REPLACE "\n" ";" RD_METHODS "${RDMethods}")

FUNCTION(GET_SUBSTRING STR BEGIN END OUT)
	SET(POS_BEGIN -1)
	SET(POS_END -1)
	STRING(FIND ${STR} ${BEGIN} POS_BEGIN)
	STRING(FIND ${STR} ${END} POS_END REVERSE)
	
	MATH(EXPR LENGTH "${POS_END} - ${POS_BEGIN} - 1")
	MATH(EXPR POS_BEGIN "${POS_BEGIN} + 1")
		
	STRING(SUBSTRING ${STR} ${POS_BEGIN} ${LENGTH} OUT_RES)
	IF (NOT ${OUT_RES} STREQUAL "")
		STRING(STRIP ${OUT_RES} OUT_RES)
	ENDIF()
	SET(${OUT} ${OUT_RES} PARENT_SCOPE)
ENDFUNCTION()

FUNCTION(PARSE_STR_FUNC IN_STR OUT_RETURN OUT_NAME)
	STRING(FIND ${IN_STR} " " POS_1)
	STRING(SUBSTRING ${IN_STR} 0 ${POS_1} STR_RETURN)
	STRING(STRIP ${STR_RETURN} STR_RETURN)
	SET(${OUT_RETURN} ${STR_RETURN} PARENT_SCOPE)
	
	STRING(FIND ${IN_STR} "(" POS_2)
	
	IF (NOT ${POS_2} STREQUAL "-1")
		MATH(EXPR LENGTH_2 "${POS_2} - ${POS_1}")
		STRING(SUBSTRING ${IN_STR} ${POS_1} ${LENGTH_2} STR_NAME)
		STRING(STRIP ${STR_NAME} STR_NAME)
		SET(${OUT_NAME} ${STR_NAME} PARENT_SCOPE)
	ENDIF()
ENDFUNCTION()

FUNCTION(REMOVE_STR IN_STR BEGIN END OUT_STR)
	STRING(LENGTH ${IN_STR} LENGTH)
	STRING(SUBSTRING ${IN_STR} 0 ${BEGIN} FIRST_STR)
	MATH(EXPR LENGTH_2 "${LENGTH} - ${END} - 1")
	STRING(SUBSTRING ${IN_STR} ${END} ${LENGTH_2} SECOND_STR)
	STRING(CONCAT RES ${FIRST_STR} ${SECOND_STR})
	SET(${OUT_STR} ${RES} PARENT_SCOPE)
ENDFUNCTION()

SET(RDMETHOD_PREFIX RD_AUTO_GEN)

FOREACH(STR ${RD_METHODS})
    SET(IS_CORRECT -1)
	STRING(FIND ${STR} ${RDMETHOD_PREFIX} IS_CORRECT)

	IF (NOT ${IS_CORRECT} EQUAL -1)
		STRING(REPLACE ${RDMETHOD_PREFIX} "" FUNC ${STR})
		STRING(REPLACE ";" "" FUNC ${FUNC})
		STRING(STRIP ${FUNC} FUNC)
		
		#GET_SUBSTRING(${STR} "(" ")" FUNC)
		#MESSAGE(-- ${FUNC})
		PARSE_STR_FUNC(${FUNC} F_RETURN F_NAME)
		#MESSAGE(${F_RETURN})
		#MESSAGE(${F_NAME})
		
		IF (NOT ${F_NAME} STREQUAL "" AND NOT ${F_RETURN} STREQUAL "")
			STRING(REGEX REPLACE "Ref$" "" FF_RETURN ${F_RETURN})
			#MESSAGE(${FF_RETURN})
			#MESSAGE(${F_RETURN})
		
			SET(DEFAULT_RET)
			
			IF (NOT ${FF_RETURN} STREQUAL ${F_RETURN})
				SET(DEFAULT_RET "return new ${FF_RETURN}()")
			ELSEIF (NOT ${F_RETURN} STREQUAL "void")
				SET(DEFAULT_RET "return 0")
			ENDIF()
				
			SET(F_PARAMS)
			GET_SUBSTRING(${FUNC} "(" ")" F_PARAMS)

			SET(F_PARAMS_FOR_CALL)		
			IF (NOT ${F_PARAMS} STREQUAL "")
				#MESSAGE(${F_PARAMS})
				STRING(REGEX REPLACE "," ";" LIST_PAIR_PARAMS "${F_PARAMS}")
						
				FOREACH(PAIR_PARAMS ${LIST_PAIR_PARAMS})
					STRING(STRIP ${PAIR_PARAMS} PAIR_PARAMS)
					STRING(FIND ${PAIR_PARAMS} " " POS REVERSE)
					STRING(SUBSTRING ${PAIR_PARAMS} 0 ${POS} TYPE_NAME)
					STRING(LENGTH ${PAIR_PARAMS} LEN)
					MATH(EXPR LEN "${LEN} - ${POS}")
					STRING(SUBSTRING ${PAIR_PARAMS} ${POS} ${LEN} PARAM_NAME)
					
					#MESSAGE(${TYPE_NAME} " -- " ${PARAM_NAME})
					
					SET(F_PARAMS_FOR_CALL "${F_PARAMS_FOR_CALL}, ${PARAM_NAME} ")
				ENDFOREACH()
			
				REMOVE_STR(${F_PARAMS_FOR_CALL} 0 1 F_PARAMS_FOR_CALL)		
				#MESSAGE((${F_PARAMS_FOR_CALL}))
			ENDIF()
		
			FILE(APPEND ${OUT_RD_IMPL_NAME} "RD_FUNC_IMPL_DEFS(${F_RETURN}, ${F_NAME}, (${F_PARAMS}), (${F_PARAMS_FOR_CALL}), ${DEFAULT_RET}) \n")
		
		ENDIF()
		
	ENDIF()
	
ENDFOREACH()