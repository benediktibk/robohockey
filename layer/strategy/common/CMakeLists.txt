FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

set(LAYER_STRATEGY_COMMON_SRC
	state.cpp
	statemachine.cpp
	refereeimpl.cpp
	drivetostate.cpp
	colordependentpucktargetfetcher.cpp
	colordependentpucktargetfetchertoachivegoals.cpp
	colordependentpucktargetfetchertohidepucks.cpp
	waitcyclesstate.cpp
)

set(LAYER_STRATEGY_COMMON_TEST_SRC
	statemock.cpp
	statemachinetest.cpp
	refereemock.cpp
	drivetostatetest.cpp
	colordependentpucktargetfetchertoachivegoalstest.cpp
	colordependentpucktargetfetchertohidepuckstest.cpp
	statetest.cpp
	colordependentpucktargetfetchermock.cpp
	waitcyclesstatetest.cpp
)

set(MOC_H
	refereeimpl.h
)

QT4_WRAP_CPP( MOC_CPP ${MOC_H} )
add_library(layerstrategycommon ${LAYER_STRATEGY_COMMON_SRC} ${MOC_CPP})
add_library(layerstrategycommontest ${LAYER_STRATEGY_COMMON_TEST_SRC} ${MOC_CPP})
