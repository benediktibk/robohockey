set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_library(CPPUNIT_LIBRARY cppunit)
include(UsePlayerC++)
find_package(OpenCV REQUIRED)
find_package(Qt4 COMPONENTS QtCore QtGui QtDeclarative QtNetwork QtXml REQUIRED)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

# on some machines this one seems not to be set properly
set(QT_LIBRARIES
	${QT_QTCORE_LIBRARY}
	${QT_QTGUI_LIBRARY}
	${QT_QTDECLARATIVE_LIBRARY}
	${QT_QTNETWORK_LIBRARY}
	${QT_QTXML_LIBRARY}
)

set(MAIN_SRC
	game.cpp
	gameautomatic.cpp
	gameremotecontrol.cpp
	inputargumentparser.cpp
)

set(MAIN_TEST_SRC
	inputargumentparsertest.cpp
)

set(MAIN_HEADERS
	game.h
)

qt4_wrap_cpp(MAIN_HEADERS_MOC ${MAIN_HEADERS})

add_library(main ${MAIN_SRC} ${MAIN_HEADERS_MOC})

set(LIBRARIES
	main
	layerview
	layerstrategymainstatemachine
	layerstrategydrivepuckstatemachine
	layerstrategyfielddetectionstatemachine
	layerstrategycommon
	layerautonomous
	layerdataanalysis
	layerhardware
	common
	referee
	${QT_LIBRARIES}
	${PLAYERCPP_LINK_LIBS}
	${OpenCV_LIBS}
)

if(Boost_FOUND)
	set(LIBRARIES
		${LIBRARIES}
		${Boost_SYSTEM_LIBRARY}
		${Boost_FILESYSTEM_LIBRARY}
	)
endif()

set(LIBRARIES_TEST
	maintest
	layerstrategymainstatemachinetest
	layerstrategyfielddetectionstatemachinetest
	layerstrategydrivepuckstatemachinetest
	layerstrategycommontest
	layerviewtest
	layerautonomoustest
	layerdataanalysistest
	layerhardwaretest
	commontest
	${CPPUNIT_LIBRARY}
)

add_library(maintest ${MAIN_TEST_SRC})

add_executable(robot main.cpp)
add_executable(testrunner testregistration.cpp maintestrunner.cpp)
add_executable(livedatatestrunner testregistrationlivedata.cpp maintestrunner.cpp)
add_executable(calibratecamera maincameracalibration.cpp)
add_executable(datalogger maindatalogger.cpp)
add_executable(remotecontrol mainremotecontrol.cpp)
add_executable(collisiondetection maincollisiondetection.cpp)

target_link_libraries(robot ${LIBRARIES})
target_link_libraries(testrunner ${LIBRARIES_TEST} ${LIBRARIES})
target_link_libraries(livedatatestrunner ${LIBRARIES_TEST} ${LIBRARIES})
target_link_libraries(calibratecamera ${LIBRARIES})
target_link_libraries(datalogger ${LIBRARIES})
target_link_libraries(remotecontrol ${LIBRARIES})
target_link_libraries(collisiondetection ${LIBRARIES})

