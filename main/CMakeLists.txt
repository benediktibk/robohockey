set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_library(CPPUNIT_LIBRARY cppunit)
include(UsePlayerC++)
find_package(OpenCV REQUIRED)
find_package(Qt4 COMPONENTS QtCore QtGui QtDeclarative QtNetwork QtXml REQUIRED)
include(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

# on some machines this one seems not to be set properly
set(QT_LIBRARIES
	${QT_QTCORE_LIBRARY}
	${QT_QTGUI_LIBRARY}
	${QT_QTDECLARATIVE_LIBRARY}
	${QT_QTNETWORK_LIBRARY}
	${QT_QTXML_LIBRARY}
)

set(LIBRARIES
	layerstrategy
	layerautonomous
	layerdataanalysis
	layerhardware
	common
	referee
	${QT_LIBRARIES}
	${PLAYERCPP_LINK_LIBS}
	${OpenCV_LIBS}
	boost_thread-mt
)

set(LIBRARIES_REMOTECONTROL
	layerview
)

set(LIBRARIES_TEST
	layerstrategytest
	layerviewtest
	layerautonomoustest
	layerdataanalysistest
	layerhardwaretest
	commontest
	${CPPUNIT_LIBRARY}
)

add_executable(robot main.cpp)
add_executable(testrunner testregistration.cpp maintestrunner.cpp)
add_executable(calibratecamera maincameracalibration.cpp)
add_executable(datalogger maindatalogger.cpp)
add_executable(remotecontrol mainremotecontrol.cpp)
add_executable(collisiondetection maincollisiondetection.cpp)

target_link_libraries(robot ${LIBRARIES})
target_link_libraries(testrunner ${LIBRARIES_TEST} ${LIBRARIES_REMOTECONTROL} ${LIBRARIES})
target_link_libraries(calibratecamera ${LIBRARIES})
target_link_libraries(datalogger ${LIBRARIES})
target_link_libraries(remotecontrol ${LIBRARIES_REMOTECONTROL} ${LIBRARIES})
target_link_libraries(collisiondetection ${LIBRARIES})

