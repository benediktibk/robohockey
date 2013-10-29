set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_library(CPPUNIT_LIBRARY cppunit)
include(UsePlayerC++)
find_package(OpenCV REQUIRED)

set(LIBRARIES
	layerdataanalysis
	layerhardware
	threading
	common
	${PLAYERCPP_LINK_LIBS}
	${OpenCV_LIBS}
	boost_thread-mt
)

set(LIBRARIES_TEST
	layerdataanalysistest
	layerhardwaretest
	threadingtest
	commontest
	${CPPUNIT_LIBRARY}
)

add_executable(robot main.cpp)
add_executable(testrunner testregistration.cpp testrunner.cpp)
target_link_libraries(robot ${LIBRARIES})
target_link_libraries(testrunner ${LIBRARIES_TEST} ${LIBRARIES})
