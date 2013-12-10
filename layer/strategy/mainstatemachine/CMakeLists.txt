FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

set(LAYER_STRATEGY_MAINSTATEMACHINE_SRC
	initialstate.cpp
	achievegoals.cpp
	calibrate.cpp
	refereeimpl.cpp
	pause.cpp
	hideenemypucks.cpp
	drivetofinalposition.cpp
)

set(LAYER_STRATEGY_MAINSTATEMACHINE_TEST_SRC
	initialstatetest.cpp
	calibratetest.cpp
	refereemock.cpp
	achievegoalstest.cpp
	hideenemypuckstest.cpp
	pausetest.cpp
	drivetofinalpositiontest.cpp
)

set(MOC_H
	refereeimpl.h
)
QT4_WRAP_CPP( MOC_CPP ${MOC_H} )
add_library(layerstrategymainstatemachine ${LAYER_STRATEGY_MAINSTATEMACHINE_SRC} ${MOC_CPP})
add_library(layerstrategymainstatemachinetest ${LAYER_STRATEGY_MAINSTATEMACHINE_TEST_SRC} ${MOC_CPP})
