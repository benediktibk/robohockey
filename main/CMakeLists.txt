set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_library(CPPUNIT_LIBRARY cppunit)
include(UsePlayerC++)
find_package(OpenCV REQUIRED)
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

set(LIBRARIES
	layerautonomous
	layerdataanalysis
	layerhardware
	threading
	common
	${PLAYERCPP_LINK_LIBS}
	${OpenCV_LIBS}
	boost_thread-mt
)

set(LIBRARIES_REMOTECONTROL
	layerview
	${LIBRARIES}
)

set(LIBRARIES_TEST
	layerautonomoustest
	layerdataanalysistest
	layerhardwaretest
	threadingtest
	commontest
	${CPPUNIT_LIBRARY}
)

add_executable(robot main.cpp)
add_executable(testrunner testregistration.cpp testrunner.cpp)
add_executable(calibratecamera cameracalibration.cpp)
add_executable(datalogger datalogger.cpp)

target_link_libraries(robot ${LIBRARIES})
target_link_libraries(testrunner ${LIBRARIES_TEST} ${LIBRARIES})
target_link_libraries(calibratecamera ${LIBRARIES})
target_link_libraries(datalogger ${LIBRARIES})
