cmake_minimum_required(VERSION 2.8)
project(robohockey)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE debug)
endif()

set(CMAKE_CXX_FLAGS_COMMON "-Wall -Wextra -Werror -ansi -fPIE -Wswitch-enum")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_COMMON} -O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_COMMON} -g")
set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_COMMON} -g -fprofile-arcs -ftest-coverage")

list(APPEND CMAKE_MODULE_PATH /usr/local/share/cmake/Modules)

include_directories(
	.
)

add_custom_target(
		checkIncludeGuards ALL
		COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/checkIncludeGuards.sh
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)

add_custom_target(
	testcoverage
	${CMAKE_CURRENT_SOURCE_DIR}/testCoverage.sh ${CMAKE_CURRENT_SOURCE_DIR}
	DEPENDS testrunner
)

find_package(Doxygen)
if(DOXYGEN_FOUND)
execute_process(COMMAND hg identify -n
				OUTPUT_VARIABLE HG_CURRENT_REV)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

add_custom_target(

	doc

	rm -f ${CMAKE_CURRENT_BINARY_DIR}/documentation/html/formula.repository && ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile 2>&1 | grep -v "stl_vector.h" | grep -v "parameter '__"

	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}

	COMMENT "Generating API documentation with Doxygen" VERBATIM

	DEPENDS ${COMMON_SRC} ${COMMON_TEST_SRC}

)
endif(DOXYGEN_FOUND)

FILE(GLOB TESTFILES_LOOSING_PUCK_1_TXT ${CMAKE_CURRENT_SOURCE_DIR}/resources/testfiles/loosing_puck_1/*.txt)
FILE(GLOB TESTFILES_LOOSING_PUCK_1_PNG ${CMAKE_CURRENT_SOURCE_DIR}/resources/testfiles/loosing_puck_1/*.png)
FILE(GLOB TESTFILES_LOOSING_PUCK_2_TXT ${CMAKE_CURRENT_SOURCE_DIR}/resources/testfiles/loosing_puck_2/*.txt)
FILE(GLOB TESTFILES_LOOSING_PUCK_2_PNG ${CMAKE_CURRENT_SOURCE_DIR}/resources/testfiles/loosing_puck_2/*.png)
FILE(GLOB TESTFILES_FIELD_DETECTION_PERFECT_TXT ${CMAKE_CURRENT_SOURCE_DIR}/resources/testfiles/field_detection_perfect/*.txt)
FILE(GLOB TESTFILES_FIELD_DETECTION_PERFECT_PNG ${CMAKE_CURRENT_SOURCE_DIR}/resources/testfiles/field_detection_perfect/*.png)
FILE(GLOB TESTFILES_FIELD_DETECTION_WORST_CASE_TXT ${CMAKE_CURRENT_SOURCE_DIR}/resources/testfiles/field_detection_worst_case/*.txt)
FILE(GLOB TESTFILES_FIELD_DETECTION_WORST_CASE_PNG ${CMAKE_CURRENT_SOURCE_DIR}/resources/testfiles/field_detection_worst_case/*.png)
FILE(GLOB TESTFILES_FIELD_DETECTION_1_TXT ${CMAKE_CURRENT_SOURCE_DIR}/resources/testfiles/field_detection_1/*.txt)
FILE(GLOB TESTFILES_FIELD_DETECTION_1_PNG ${CMAKE_CURRENT_SOURCE_DIR}/resources/testfiles/field_detection_1/*.png)
FILE(GLOB TESTFILES_TXT ${CMAKE_CURRENT_SOURCE_DIR}/resources/testfiles/*.txt)
FILE(GLOB TESTFILES_PNG ${CMAKE_CURRENT_SOURCE_DIR}/resources/testfiles/*.png)

set(TESTFILES
	${TESTFILES_TXT}
	${TESTFILES_PNG}
)

set(TESTFILES_LOOSING_PUCK_1
	${TESTFILES_LOOSING_PUCK_1_TXT}
	${TESTFILES_LOOSING_PUCK_1_PNG}
)

set(TESTFILES_LOOSING_PUCK_2
	${TESTFILES_LOOSING_PUCK_2_TXT}
	${TESTFILES_LOOSING_PUCK_2_PNG}
)


set(TESTFILES_FIELD_DETECTION_PERFECT
	${TESTFILES_FIELD_DETECTION_PERFECT_TXT}
	${TESTFILES_FIELD_DETECTION_PERFECT_PNG}
)

set(TESTFILES_FIELD_DETECTION_1
	${TESTFILES_FIELD_DETECTION_1_TXT}
	${TESTFILES_FIELD_DETECTION_1_PNG}
)

set(TESTFILES_FIELD_DETECTION_WORST_CASE
	${TESTFILES_FIELD_DETECTION_WORST_CASE_TXT}
	${TESTFILES_FIELD_DETECTION_WORST_CASE_PNG}
)

foreach(file ${TESTFILES})
	file(	COPY
			${file}
			DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/main/bin/resources/testfiles/)
endforeach()

foreach(file ${TESTFILES_LOOSING_PUCK_1})
	file(	COPY
			${file}
			DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/main/bin/resources/testfiles/loosing_puck_1)
endforeach()

foreach(file ${TESTFILES_LOOSING_PUCK_2})
	file(	COPY
			${file}
			DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/main/bin/resources/testfiles/loosing_puck_2)
endforeach()

foreach(file ${TESTFILES_FIELD_DETECTION_PERFECT})
	file(	COPY
			${file}
			DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/main/bin/resources/testfiles/field_detection_perfect)
endforeach()

foreach(file ${TESTFILES_FIELD_DETECTION_WORST_CASE})
	file(	COPY
			${file}
			DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/main/bin/resources/testfiles/field_detection_worst_case)
endforeach()

foreach(file ${TESTFILES_FIELD_DETECTION_1})
	file(	COPY
			${file}
			DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/main/bin/resources/testfiles/field_detection_1)
endforeach()

add_subdirectory(common)
add_subdirectory(layer)
add_subdirectory(main)
add_subdirectory(extern)