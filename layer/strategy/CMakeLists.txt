FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

set(LAYER_STRATEGY_SRC
	state.cpp
	statemachine.cpp
	initialstate.cpp
	achievegoals.cpp
	calibrate.cpp
	refereeimpl.cpp
)

set(LAYER_STRATEGY_TEST_SRC
	statemock.cpp
	statemachinetest.cpp
	initialstatetest.cpp
	refereemock.cpp
)

set(MOC_H
	refereeimpl.h
)
QT4_WRAP_CPP( MOC_CPP ${MOC_H} )
add_library(layerstrategy ${LAYER_STRATEGY_SRC} ${MOC_CPP})
add_library(layerstrategytest ${LAYER_STRATEGY_TEST_SRC} ${MOC_CPP})
