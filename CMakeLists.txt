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

add_subdirectory(common)
add_subdirectory(layer)
add_subdirectory(main)
add_subdirectory(extern)

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

set(TESTFILES
	lidar_1.txt
	lidar_2.txt
	lidar_3.txt
	lidar_4.txt
	lidar_5.txt
	lidar_6.txt
	lidar_7.txt
	lidar_8.txt
	lidar_9.txt
	lidar_10.txt
	lidar_11.txt
	lidar_12.txt
	lidar_13.txt
	lidar_14.txt
	lidar_15.txt
	lidar_16.txt
	lidar_17.txt
	lidar_18.txt
	lidar_19.txt
	lidar_20.txt
	lidar_21.txt
	lidar_22.txt
	lidar_23.txt
	lidar_24.txt
	lidar_25.txt
	lidar_26.txt
	lidar_27.txt
	lidar_28.txt
	lidar_29.txt
	lidar_30.txt
	lidar_31.txt
	lidar_32.txt
	lidar_33.txt
	lidar_34.txt
	lidar_35.txt
	lidar_36.txt
	lidar_37.txt
	lidar_38.txt
	lidar_39.txt
	lidar_wall.txt
	sonar_1.txt
	sonar_2.txt
	sonar_3.txt
	sonar_4.txt
	sonar_5.txt
	sonar_6.txt
	blue_goal.png
	blue_puck.png
	nothing.png
	yellow_and_blue_puck.png
	yellow_goal.png
	yellow_puck.png
	yellow_puck_twice.png
	yellow_goal_1.png
	green_borderstone.png
	green_borderstone_1.png
	green_borderstone_triple.png
	green_borderstone_triple_1.png
	yellow_and_blue_puck_and_green_borderstone.png
	yellow_puck_twice_and_green_borderstone.png
	yellow_puck_twice_and_green_borderstone_1.png
	camera_22_11.png
	lidar_detect1.txt
	lidar_detect2.txt
	lidar_detect3.txt
	yellow_puck_collected_left.png
	yellow_puck_collected_right.png
	yellow_puck_collected_left_2.png
	yellow_puck_collected_right_2.png
	yellow_puck_collected_in_blue_goal_2.png
	blue_puck_collected_left.png
	blue_puck_collected_right.png
	blue_puck_collected_in_yellow_goal.png
)

foreach(file ${TESTFILES})
	file(	COPY
			${CMAKE_CURRENT_SOURCE_DIR}/resources/testfiles/${file}
			DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/main/bin/resources/testfiles/)
endforeach()
